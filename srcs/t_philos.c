/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:50:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 16:40:23 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	init_philo(t_philo *p)
{
	p->r_frk_id = p->p_id - 1;
	p->l_frk_id = p->p_id;
	if (p->r_frk_id == 0)
		p->r_frk_id = p->in->nb_p;
	p->plts_max = p->in->plts_p_philo;
	p->is_even = p->p_id % 2;
	p->alive = 1;
	gettimeofday(&p->lst_meal, NULL);
	pthread_mutex_init(&p->plts_lock, NULL);
	pthread_mutex_init(&p->alive_lock, NULL);
}

static int	circle_states(t_philo	*p)
{
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_eat(p))
			return (0);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_sleep(p))
			return (0);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_think(p))
			return (0);
	return (1);
}

static int	smol_circle_states(t_philo	*p)
{
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_think(p))
			return (0);
	if (p->p_id == p->in->nb_p)
		ft_usleep(p->in->time_eat * 2);
	else
		ft_usleep(p->in->time_eat);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_eat(p))
			return (0);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_sleep(p))
			return (0);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		if (did_p_died(p->s_in) || !p_think(p))
			return (0);
	return (1);
}

void	*philosopher(void *philosoher)
{
	t_philo	*p;

	p = (t_philo *)philosoher;
	init_philo(p);
	while (p->alive == 1 && p->plts_eaten < p->plts_max)
	{
		if ((p->plts_eaten == 0 && p->is_even == 0) || \
		(p->plts_eaten != 0 && p->plts_eaten < p->plts_max && \
		p->alive == 1))
		{
			if (!circle_states(p))
				break ;
		}
		else if (p->plts_eaten == 0 && p->is_even == 1)
		{
			if (!smol_circle_states(p))
				break ;
		}
	}
	if (p->alive)
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status("DONE", p->p_id, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
	}
	return (NULL);
}
