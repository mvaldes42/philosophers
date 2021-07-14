/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_death_clock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:51:41 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 14:51:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	death_scenario(t_innkeper *inn, int i, long int x)
{
	pthread_mutex_lock(&inn->s_in.talk_lock);
	printf("death clock\n");
	say_death_status(inn->p[i].p_id, inn->in_ptr.start_time, \
	inn->p[i].lst_meal);
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
	int				plts_eat;

	i = 1;
	while (i <= inn->in_ptr.nb_p && inn->no_death)
	{
		pthread_mutex_lock(&inn->p[i].plts_lock);
		plts_eat = inn->p[i].plts_eaten;
		pthread_mutex_unlock(&inn->p[i].plts_lock);
		if (first_time)
		{
			ft_usleep(5);
			first_time = 0;
		}
		gettimeofday(&time, NULL);
		x = from_time_to_ms(time) - from_time_to_ms(inn->p[i].lst_meal);
		if (plts_eat == inn->in_ptr.plts_p_philo || x <= inn->in_ptr.time_die)
			i++;
		if (plts_eat != inn->in_ptr.plts_p_philo && x > inn->in_ptr.time_die)
			death_scenario(inn, i, x);
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
		ft_usleep(5);
	}
	return (NULL);
}
