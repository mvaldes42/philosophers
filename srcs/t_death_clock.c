/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_death_clock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:51:41 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 15:24:33 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	death_scenario(t_innkeper *inn, int i, long int x, struct timeval t)
{
	x = from_time_to_ms(t) - from_time_to_ms(inn->p[i].lst_meal);
	pthread_mutex_lock(&inn->s_in.talk_lock);
	say_status_nb("is dead", inn->p[i].p_id, x, inn->in_ptr.start_time);
	pthread_mutex_unlock(&inn->s_in.talk_lock);
	inn->p[i].alive = 0;
	inn->no_death = 0;
	exit_success(inn);
}

static void	check_if_death(t_innkeper *inn, int first_time)
{
	long int		x;
	struct timeval	time;
	int				i;

	i = 1;
	while (i <= inn->in_ptr.nb_p)
	{
		if (first_time)
		{
			ft_usleep(inn->in_ptr.time_die);
			first_time = 0;
		}
		gettimeofday(&time, NULL);
		x = from_time_to_ms(time) - from_time_to_ms(inn->p[i].lst_meal);
		if (x < inn->in_ptr.time_die)
			i++;
		else if (x >= inn->in_ptr.time_die)
			death_scenario(inn, i, x, time);
	}
}

void	*are_philo_dead(void *innkeeper)
{
	t_innkeper		*inn;
	int				first_time;

	inn = (t_innkeper *)innkeeper;
	inn->no_death = 1;
	first_time = 1;
	while (inn->no_death)
	{
		check_if_death(inn, first_time);
		ft_usleep(inn->in_ptr.time_die / 2);
	}
	return (NULL);
}

void	*am_i_dead(void *philosopher)
{
	t_philo			*p;
	struct timeval	time;
	int				x;

	p = (t_philo *)philosopher;
	ft_usleep(p->in->time_die);
	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x >= p->in->time_die)
	{
		p->alive = 0;
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status_nb("ISSS DEEEEAAAAAAADDD", p->p_id, x, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
		exit(EXIT_SUCCESS);
	}
	return (NULL);
}
