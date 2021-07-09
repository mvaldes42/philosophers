/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/09 19:25:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// milliseconds = microseconds ÷ 1,000

//4 410 200 200
// 5 800 200 200
// 4 310 200 100 (mort)
// Avec 2 philosophes seulement pour tester le delai d'affichage de la mort
// ya aussi 5 800 200 200 7
// et 1 800 200 200 (depuis recemment)

long int	from_time_to_ms(struct timeval what_time)
{
	long int	ms;

	ms = what_time.tv_sec * 1000 + what_time.tv_usec / 1000;
	return (ms);
}

void	init_inputs(int argc, char **argv, t_innkeper *inn)
{
	t_inputs	*inputs;

	inputs = &inn->in_ptr;
	memset(inputs, 0, sizeof(*inputs));
	memset(&inn->shared_in, 0, sizeof(inn->shared_in));
	if (argc < 4)
		exit_failure(inn);
	inn->philo = malloc((inn->in_ptr.nb_philo + 1) * sizeof(inn->philo));
	inn->shared_in.forks_lock = malloc((inn->in_ptr.nb_philo + 1) * sizeof(inn->shared_in.forks_lock));
	gettimeofday(&inn->current_time, NULL);
	inn->shared_in.plates_lock = malloc((floor(inn->in_ptr.nb_philo / 2) + 1) * sizeof(inn->shared_in.plates_lock));
	inputs->nb_philo = atoi(argv[1]);
	inputs->time_to_die = atoi(argv[2]);
	inputs->time_to_eat = atoi(argv[3]);
	inputs->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		inputs->nb_plates_per_philo = atoi(argv[5]);
	else
		inputs->nb_plates_per_philo = -1;
	inputs->time_to_think = inputs->time_to_eat;
}

void	p_eat(t_philo *philo)
{
	struct timeval	c_time;
	int				x;

	gettimeofday(&c_time, NULL);
	x = from_time_to_ms(c_time) - from_time_to_ms(philo->time_since_last_meal);
	pthread_mutex_lock(&philo->shared_in->forks_lock[philo->right_fork_id]);
	pthread_mutex_lock(&philo->shared_in->forks_lock[philo->left_fork_id]);
	pthread_mutex_lock(&philo->shared_in->plates_lock[0]);
	philo->state = EATING;
	gettimeofday(&philo->time_since_last_meal, NULL);
	philo->shared_in->nb_total_meals_eaten++;
	philo->nb_plates_eaten++;
	pthread_mutex_lock(&philo->shared_in->talk_lock);
	printf("#%d x = %d, ttd = %d\n", philo->philo_id, x, philo->inputs->time_to_die);
	printf("#%d is eating, he ate %d plates,\n", philo->philo_id, \
	philo->nb_plates_eaten);
	pthread_mutex_unlock(&philo->shared_in->talk_lock);
	usleep(philo->inputs->time_to_eat * 1000);
	pthread_mutex_lock(&philo->shared_in->talk_lock);
	printf("#%d forks_lock down\n", philo->philo_id);
	pthread_mutex_unlock(&philo->shared_in->talk_lock);
	pthread_mutex_unlock(&philo->shared_in->plates_lock[0]);
	pthread_mutex_unlock(&philo->shared_in->forks_lock[philo->right_fork_id]);
	pthread_mutex_unlock(&philo->shared_in->forks_lock[philo->left_fork_id]);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_in->talk_lock);
	printf("#%d is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(&philo->shared_in->talk_lock);
	philo->state = SLEEPING;
	usleep(philo->inputs->time_to_sleep * 1000);
}

void	p_think(t_philo *philo)
{
	if (philo->is_alive == 1 && \
	philo->nb_plates_eaten < philo->nb_plates_allowed)
	{
		philo->state = THINKING;
		pthread_mutex_lock(&philo->shared_in->talk_lock);
		printf("#%d is thinking\n", philo->philo_id);
		pthread_mutex_unlock(&philo->shared_in->talk_lock);
	}
}

void	*philosopher(void *philosoher)
{
	t_philo	*philo;

	philo = (t_philo *)philosoher;
	philo->right_fork_id = philo->philo_id - 1;
	philo->left_fork_id = philo->philo_id;
	philo->nb_plates_allowed = philo->inputs->nb_plates_per_philo;
	philo->am_i_even = philo->philo_id % 2;
	philo->is_alive = 1;
	gettimeofday(&philo->time_since_last_meal, NULL);
	if (philo->right_fork_id == 0)
	{
		philo->right_fork_id = philo->inputs->nb_philo;
	}
	while (philo->is_alive == 1 && philo->nb_plates_eaten < philo->nb_plates_allowed)
	{
		if (philo->nb_plates_eaten == 0 && philo->am_i_even == 0)
		{
			p_eat(philo);
			p_sleep(philo);
			p_think(philo);
		}
		else if (philo->nb_plates_eaten == 0 && philo->am_i_even == 1)
		{
			p_think(philo);
			p_eat(philo);
		}
		else if (philo->nb_plates_eaten != 0 && \
		philo->nb_plates_eaten < philo->nb_plates_allowed && \
		philo->is_alive == 1)
		{
			p_eat(philo);
			p_sleep(philo);
			p_think(philo);
		}
	}
	return (NULL);
}

void	*are_philo_dead(void *innkeeper)
{
	t_innkeper		*inn;
	int				i;
	struct timeval	current_time;
	long int		x;

	inn = (t_innkeper *)innkeeper;
	inn->no_death = 1;
	while (inn->no_death)
	{
		i = 1;
		while (i <= inn->in_ptr.nb_philo)
		{
			// printf("philo #%d x = %ld, ttd = %d\n", i, x, inn->in_ptr.time_to_die);
			gettimeofday(&current_time, NULL);
			x = from_time_to_ms(current_time) - \
			from_time_to_ms(inn->philo[i].time_since_last_meal);
			if (x < inn->in_ptr.time_to_die)
				i++;
			else if (inn->philo[i].nb_plates_eaten == 0)
				usleep(10 * 1000);
			else
			{
				printf("philo #%d x = %ld, ttd = %d\n", i, x, inn->in_ptr.time_to_die);
				printf("#%d is dead\n", inn->philo[i].philo_id);
				inn->philo[i].is_alive = 0;
				inn->no_death = 0;
				exit_success(inn);
			}
		}
		usleep(5 * 1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	init_inputs(argc, argv, &inn);
	pthread_mutex_init(&inn.shared_in.talk_lock, NULL);
	inn.in_ptr.nb_plates_total = inn.in_ptr.nb_plates_per_philo * inn.in_ptr.nb_philo;
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		pthread_mutex_init(&inn.shared_in.forks_lock[i], NULL);
		i++;
	}
	pthread_create(&inn.death_clock, NULL, are_philo_dead, (void *)&inn);
	i = 1;
	while (i <= floor(inn.in_ptr.nb_philo / 2))
	{
		pthread_mutex_init(&inn.shared_in.plates_lock[i], NULL);
		i++;
	}
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		memset(&inn.philo[i], 0, sizeof(inn.philo[i]));
		inn.philo[i].philo_id = i;
		inn.philo[i].inputs = &inn.in_ptr;
		inn.philo[i].shared_in = &inn.shared_in;
		pthread_create(&inn.philo[i].thread_id, NULL, philosopher, \
		(void *)&inn.philo[i]);
		i++;
	}
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		pthread_join(inn.philo[i].thread_id, NULL);
		i++;
	}
	exit_success(&inn);
}
