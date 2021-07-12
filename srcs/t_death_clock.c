/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_death_clock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:51:41 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 16:04:29 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	death_scenario(t_innkeper *inn, int i, long int x)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("p #%d x = %ld, ttd = %d\n", i, x, inn->in_ptr.time_die);
	talk_2(&inn->s_in.talk_lock, "%d >> #%d is dead\n", \
	from_time_to_ms(time) - from_time_to_ms(inn->in_ptr.sim_start_time), \
	inn->p[i].p_id);
	inn->p[i].alive = 0;
	inn->no_death = 0;
	exit_success(inn);
}

// printf("p #%d x = %ld, ttd = %d\n", i, x, inn->in_ptr.time_die);

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
			usleep(5 * 1000);
			first_time = 0;
		}
		gettimeofday(&time, NULL);
		x = from_time_to_ms(time) - from_time_to_ms(inn->p[i].lst_meal);
		if (x < inn->in_ptr.time_die)
			i++;
		else if (x >= inn->in_ptr.time_die)
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
		usleep(5 * 1000);
	}
	return (NULL);
}
