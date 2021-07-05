/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:20 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/05 18:18:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef enum e_actions
{
	TAKING_A_FORK,
	EATING,
	DROPING_FORKS,
	SLEEPING,
	THINKING,
}	t_actions;

typedef struct s_inputs
{
	signed int	time_current;
	int			number_of_philosophers;
	signed int	time_to_die;
	signed int	time_to_eat;
	signed int	time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	t_actions	*actions;
}	t_inputs;

typedef struct s_philo
{
	int			philo_id;
	pthread_t	thread_id;
	t_inputs	inputs;
	int			right_fork_id;
	int			left_fork_id;
	bool		right_fork_locked;
	bool		left_fork_locked;
	t_actions	current_action;
	signed int	time_start_of_action;
	char		*current_status;
	signed int	time_status_printed;
	signed int	timer_to_next;
	int			philosopher_priority;
	signed int	time_since_last_meal;
	int			number_of_meals_eaten;
	bool		is_alive;
	int			erno;
}	t_philo;

typedef struct s_innkeeper
{
	t_inputs	*inputs_ptr;
	t_philo		*philosophers;
	int			nb_of_meals_left;
}	t_innkeper;

#endif