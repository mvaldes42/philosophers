/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:20 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 15:55:05 by mvaldes          ###   ########.fr       */
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
# include <string.h>
# include <stdarg.h>
# include <math.h>

typedef enum e_states
{
	EATING,
	SLEEPING,
	THINKING,
}	t_states;

typedef struct s_shared_inputs
{
	pthread_mutex_t	*frk_lck;
	pthread_mutex_t	*plts_lck;
	pthread_mutex_t	talk_lock;
	int				tot_plts_eaten;
	bool			*can_i_eat;
	pthread_mutex_t	*state_lck;
}	t_shared_in;

typedef struct s_inputs
{
	int				nb_p;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_thk;
	int				plts_p_philo;
	int				plts_tot;
	struct timeval	sim_start_time;
}	t_inputs;

typedef struct s_philo
{
	int				p_id;
	pthread_t		t_id;
	t_inputs		*inputs;
	t_shared_in		*s_in;
	int				is_even;
	int				r_frk_id;
	int				l_frk_id;
	struct timeval	lst_meal;
	int				plts_eaten;
	int				plts_max;
	bool			alive;
	bool			eating;
}	t_philo;

typedef struct s_innkeeper
{
	t_inputs		in_ptr;
	t_philo			*p;
	t_shared_in		s_in;
	pthread_t		death_clock;
	bool			no_death;
}	t_innkeper;

void	init_inputs(int argc, char **argv, t_innkeper *inn);

void	*philosopher(void *philosoher);
void	*are_philo_dead(void *innkeeper);

void	p_eat(t_philo *p);
void	p_sleep(t_philo *p);
void	p_think(t_philo *p);

#endif