/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/06 18:36:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// milliseconds = microseconds ÷ 1,000
// struct object{
//         int data;
//         void (*new_func) (int * data);
// };

// void scan_data (int * data) {
//         printf(" input : ");
//         scanf("%d", data);
// }

// struct object f;
// f.new_func = scan_data;
// f.new_func(&f.data);

// void	*myThreadFun(void *input)
// {
// 	sleep(1);
// 	int *myid = (int *)input;
// 	printf("Printing GeeksQuiz from Thread %d\n", (int*)myid);
// 	return (NULL);
// }

long int	from_time_to_ms(struct timeval what_time)
{
	long int	ms;

	ms = what_time.tv_sec * 1000 + what_time.tv_usec / 1000;
	return (ms);
}

void	init_inputs(int argc, char **argv, t_innkeper *innkeeper)
{
	t_inputs	*inputs;

	inputs = &innkeeper->inputs_ptr;
	if (argc < 4)
		exit_failure(innkeeper);
	innkeeper->philo = malloc((innkeeper->inputs_ptr.nb_philo + 1) * \
	sizeof(innkeeper->philo));
	innkeeper->inputs_ptr.forks = malloc((innkeeper->inputs_ptr.nb_philo + 1) \
	* sizeof(innkeeper->philo));
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
}

void	*philosopher(void *philosoher)
{
	t_philo	*philo;

	philo = (t_philo *)philosoher;
	philo->right_fork_id = philo->philo_id - 1;
	philo->left_fork_id = philo->philo_id;
	if (philo->right_fork_id == 0)
		philo->right_fork_id = philo->inputs->nb_philo;
	while (philo->number_of_meals_eaten < philo->inputs->nb_plates)
	{
		// printf("#%d prio is %d\n", philo->philo_id, philo->priority_to_eat);
		if (philo->priority_to_eat == 1)
		{
			philo->number_of_meals_eaten ++;
			printf("#%d is eating\n", philo->philo_id);
			usleep(1000000);
			philo->priority_to_eat = 0;
		}
	}
	return (NULL);
}

void	innkeeper_job(t_innkeper *innkeeper)
{
	int	i;

	innkeeper->nb_of_meals_total = innkeeper->inputs_ptr.nb_plates * \
	innkeeper->inputs_ptr.nb_philo;
	innkeeper->nb_of_meals_eaten = 0;
	while (innkeeper->nb_of_meals_eaten < innkeeper->nb_of_meals_total)
	{
		i = 1;
		while (i <= innkeeper->inputs_ptr.nb_philo)
		{
			printf("innkeeper->nb_of_meals_eaten=%d\n", innkeeper->nb_of_meals_eaten);
			if (innkeeper->philo[i].number_of_meals_eaten == 0 && \
			innkeeper->philo[i].philo_id % 2 == 0)
			{
				innkeeper->philo[i].priority_to_eat = 1;
				innkeeper->nb_of_meals_eaten++;
				// printf("#%d prio is 1\n", innkeeper->philo[i].philo_id);
			}
			else if (innkeeper->philo[i].priority_to_eat == 0)
			{
				innkeeper->philo[i].priority_to_eat = 1;
				innkeeper->nb_of_meals_eaten++;
			}
			i++;
		}
	}
}
int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	innkeeper;

	memset(&innkeeper, 0, sizeof(innkeeper));
	init_inputs(argc, argv, &innkeeper);
	i = 1;
	while (i <= innkeeper.inputs_ptr.nb_philo)
	{
		pthread_mutex_init(&innkeeper.inputs_ptr.forks[i], NULL);
		i++;
	}
	i = 1;
	while (i <= innkeeper.inputs_ptr.nb_philo)
	{
		innkeeper.philo[i].philo_id = i;
		innkeeper.philo[i].inputs = &innkeeper.inputs_ptr;
		pthread_create(&innkeeper.philo[i].thread_id, NULL, philosopher, \
		(void *)&innkeeper.philo[i]);
		i++;
	}
	innkeeper_job(&innkeeper);
	i = 1;
	while (i <= innkeeper.inputs_ptr.nb_philo)
	{
		pthread_join(innkeeper.philo[i].thread_id, NULL);
		i++;
	}
	// pthread_mutex_init (&food_lock, NULL);
	// pthread_mutex_init (&num_can_eat_lock, NULL);
	// for (i = 0; i < PHILOS; i++)
	// pthread_mutex_init (&chopstick[i], NULL);
	exit_success(&innkeeper);
}
