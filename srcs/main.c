/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/07 15:02:51 by mvaldes          ###   ########.fr       */
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
	if (argc < 4)
		exit_failure(inn);
	inn->philo = malloc((inn->in_ptr.nb_philo + 1) * sizeof(inn->philo));
	inn->in_ptr.forks = malloc((inn->in_ptr.nb_philo + 1) * sizeof(inn->philo));
	gettimeofday(&inputs->current_time, NULL);
	inputs->start_sim_ms = from_time_to_ms(inputs->current_time);
	printf("start_sim_ms = %ld\n", inputs->start_sim_ms);
	inputs->nb_philo = atoi(argv[1]);
	inputs->time_to_die = atoi(argv[2]);
	inputs->time_to_eat = atoi(argv[3]);
	inputs->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		inputs->nb_plates = atoi(argv[5]);
	else
		inputs->nb_plates = -1;
	inputs->time_to_think = inputs->time_to_eat;
}

void	p_eat(t_philo *philo)
{
	if (philo->inputs->nb_meals_eaten < philo->inputs->nb_meals_tot && \
	philo->number_of_meals_eaten < philo->inputs->nb_plates &&\
	philo->is_alive == 1)
	{
		pthread_mutex_lock(&philo->inputs->forks[philo->right_fork_id]);
		pthread_mutex_lock(&philo->inputs->forks[philo->left_fork_id]);
		pthread_mutex_lock(&philo->inputs->meals_lock);
		philo->inputs->nb_meals_eaten++;
		philo->number_of_meals_eaten++;
		pthread_mutex_lock(&philo->inputs->can_i_talk);
		printf("#%d is eating, he ate %d plates, for plates eaten total = %d\n"\
		, philo->philo_id, philo->number_of_meals_eaten, \
		philo->inputs->nb_meals_eaten);
		pthread_mutex_unlock(&philo->inputs->can_i_talk);
		gettimeofday(&philo->time_since_last_meal, NULL);
		usleep(philo->inputs->time_to_eat * 1000);
		pthread_mutex_lock(&philo->inputs->can_i_talk);
		printf("#%d forks down\n", philo->philo_id);
		pthread_mutex_unlock(&philo->inputs->can_i_talk);
		pthread_mutex_unlock(&philo->inputs->forks[philo->right_fork_id]);
		pthread_mutex_unlock(&philo->inputs->forks[philo->left_fork_id]);
		pthread_mutex_unlock(&philo->inputs->meals_lock);
	}
}

void	p_sleep(t_philo *philo)
{
	if (philo->inputs->nb_meals_eaten < philo->inputs->nb_meals_tot && \
	philo->number_of_meals_eaten < philo->inputs->nb_plates &&\
	philo->is_alive == 1)
	{
		pthread_mutex_lock(&philo->inputs->can_i_talk);
		printf("#%d is sleeping\n", philo->philo_id);
		pthread_mutex_unlock(&philo->inputs->can_i_talk);
		usleep(philo->inputs->time_to_sleep * 1000);
	}
}

void	p_think(t_philo *philo)
{
	if (philo->inputs->nb_meals_eaten < philo->inputs->nb_meals_tot && \
	philo->number_of_meals_eaten < philo->inputs->nb_plates &&\
	philo->is_alive == 1)
	{
		pthread_mutex_lock(&philo->inputs->can_i_talk);
		printf("#%d is thinking\n", philo->philo_id);
		pthread_mutex_unlock(&philo->inputs->can_i_talk);
	}
}

void	*philosopher(void *philosoher)
{
	t_philo	*philo;

	philo = (t_philo *)philosoher;
	philo->right_fork_id = philo->philo_id - 1;
	philo->left_fork_id = philo->philo_id;
	philo->am_i_even = philo->philo_id % 2;
	philo->is_alive = 1;
	gettimeofday(&philo->time_since_last_meal, NULL);
	printf("#%d has %d plates\n", philo->philo_id, philo->number_of_meals_eaten);
	if (philo->right_fork_id == 0)
	{
		philo->right_fork_id = philo->inputs->nb_philo;
	}
	while (philo->inputs->nb_meals_eaten < philo->inputs->nb_meals_tot && \
	philo->number_of_meals_eaten < philo->inputs->nb_plates &&\
	philo->is_alive == 1)
	{
		if (philo->inputs->nb_meals_eaten == 0 && philo->am_i_even == 0)
		{
			pthread_mutex_lock(&philo->inputs->can_i_talk);
			printf("#%d / 2 = %d\n", philo->philo_id, philo->am_i_even);
			pthread_mutex_unlock(&philo->inputs->can_i_talk);
			p_eat(philo);
			p_sleep(philo);
			p_think(philo);
		}
		else if (philo->inputs->nb_meals_eaten == 0 && philo->am_i_even == 1)
		{
			pthread_mutex_lock(&philo->inputs->can_i_talk);
			printf("#%d / 2 = %d\n", philo->philo_id, philo->am_i_even);
			pthread_mutex_unlock(&philo->inputs->can_i_talk);
			p_think(philo);
		}
		else if (philo->inputs->nb_meals_eaten != 0)
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

	inn = (t_innkeper *)innkeeper;
	inn->in_ptr.no_one_dead = 1;
	while (inn->in_ptr.no_one_dead)
	{
		i = 1;
		while (i <= inn->in_ptr.nb_philo)
		{
			gettimeofday(&current_time, NULL);
			if (from_time_to_ms(current_time) - \
			from_time_to_ms(inn->philo[i].time_since_last_meal) < \
			inn->in_ptr.time_to_die)
				i++;
			else
			{
				printf("#%d is dead\n", inn->philo[i].philo_id);
				inn->in_ptr.no_one_dead = 0;
				exit_success(inn);
			}
		}
		usleep(10 * 1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	init_inputs(argc, argv, &inn);
	pthread_mutex_init(&inn.in_ptr.meals_lock, NULL);
	pthread_mutex_init(&inn.in_ptr.can_i_talk, NULL);
	inn.in_ptr.nb_meals_tot = inn.in_ptr.nb_plates * inn.in_ptr.nb_philo;
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		pthread_mutex_init(&inn.in_ptr.forks[i], NULL);
		i++;
	}
	pthread_create(&inn.death_clock, NULL, are_philo_dead, (void *)&inn);
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		memset(&inn.philo[i], 0, sizeof(inn.philo[i]));
		inn.philo[i].philo_id = i;
		inn.philo[i].inputs = &inn.in_ptr;
		pthread_create(&inn.philo[i].thread_id, NULL, philosopher, \
		(void *)&inn.philo[i]);
		i++;
	}
	// innkeeper_job(&inn);
	i = 1;
	while (i <= inn.in_ptr.nb_philo)
	{
		pthread_join(inn.philo[i].thread_id, NULL);
		i++;
	}
	// pthread_mutex_init (&food_lock, NULL);
	// pthread_mutex_init (&num_can_eat_lock, NULL);
	// for (i = 0; i < PHILOS; i++)
	// pthread_mutex_init (&chopstick[i], NULL);
	exit_success(&inn);
}
