/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_death_clock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:51:41 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/16 21:54:51 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	death_scenario(t_innkeper *inn, int i, long int x)
{
	death_status_out(&inn->p[i]);
	pthread_mutex_lock(&inn->p[i].alive_lock);
	inn->p[i].alive = 0;
	pthread_mutex_unlock(&inn->p[i].alive_lock);
	inn->no_death = 0;
	pthread_mutex_lock(&inn->s_in.smne_d_lock);
	inn->s_in.smne_died = 1;
	pthread_mutex_unlock(&inn->s_in.smne_d_lock);
}

static int	check_if_death(t_innkeper *inn, int first_time)
{
	int	i;
	int	plts_eat;
	int	p_alive;

	i = 0;
	while (i < inn->in_ptr.nb_p && (inn->no_death || \
	inn->nb_completed < inn->in_ptr.nb_p))
	{
		pthread_mutex_lock(&inn->p[i].plts_lock);
		pthread_mutex_lock(&inn->p[i].alive_lock);
		plts_eat = inn->p[i].plts_eaten;
		p_alive = inn->p[i].alive;
		pthread_mutex_unlock(&inn->p[i].plts_lock);
		pthread_mutex_unlock(&inn->p[i].alive_lock);
		if (plts_eat == inn->in_ptr.plts_p_philo)
			inn->nb_completed += 1;
		else if ((time_diff_ms(inn->p[i].lst_meal) > inn->in_ptr.time_die) || \
		(p_alive == 0))
		{
			death_scenario(inn, i, time_diff_ms(inn->p[i].lst_meal));
			return (0);
		}
		i++;
	}
	return (1);
}

void	*death_check_t(void *innkeeper)
{
	t_innkeper	*inn;
	int			first_time;

	inn = (t_innkeper *)innkeeper;
	inn->nb_completed = 0;
	inn->no_death = 1;
	first_time = 1;
	while (inn->no_death && inn->nb_completed < inn->in_ptr.nb_p)
	{
		if (first_time)
		{
			ft_usleep(inn->in_ptr.time_die);
			first_time = 0;
		}
		if (!check_if_death(inn, first_time))
			break ;
		ft_usleep(5);
	}
	return (NULL);
}
