/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:50:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/16 22:26:52 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	init_philo(t_philo *p)
{
	p->r_frk_id = p->p_id - 1;
	p->l_frk_id = p->p_id;
	if (p->r_frk_id == 0)
		p->r_frk_id = p->in->nb_p - 1;
	p->plts_max = p->in->plts_p_philo;
	p->is_odd = p->p_id % 2;
	pthread_mutex_lock(&p->alive_lock);
	p->alive = 1;
	pthread_mutex_unlock(&p->alive_lock);
	gettimeofday(&p->lst_meal, NULL);
}

static int	circle_states(t_philo	*p)
{
	long long	plts_tot;

	pthread_mutex_lock(&p->s_in->plts_e_tot_lock);
	plts_tot = p->s_in->plts_e_tot;
	pthread_mutex_unlock(&p->s_in->plts_e_tot_lock);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_eat(p))
			return (0);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_sleep(p))
			return (0);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_think(p))
			return (0);
	if (p->in->nb_p % 2 == 1 && plts_tot < p->in->nb_p && p->p_id == \
	p->in->nb_p - 2)
		ft_usleep(p->in->time_eat);
	return (1);
}

static int	smol_circle_states(t_philo	*p)
{
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_think(p))
			return (0);
	if (p->p_id == p->in->nb_p - 1)
		ft_usleep_states(p->in->time_eat * 2, p);
	else
		ft_usleep_states(p->in->time_eat, p);
	if (did_i_died(p))
		return (0);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_eat(p))
			return (0);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_sleep(p))
			return (0);
	if (!did_i_died(p) && p->plts_eaten < p->plts_max)
		if (did_e_died(p->s_in) || !p_think(p))
			return (0);
	return (1);
}

void	*philo_t(void *philosoher)
{
	t_philo	*p;

	p = (t_philo *)philosoher;
	init_philo(p);
	while (!did_i_died(p) && !did_e_died(p->s_in))
	{
		if (p->in->nb_p <= 1)
			;
		else if ((p->plts_eaten == 0 && p->is_odd == 1) || p->plts_eaten != 0)
		{
			if (!circle_states(p))
				break ;
		}
		else if (p->plts_eaten == 0 && p->is_odd == 0)
		{
			if (!smol_circle_states(p))
				break ;
		}
		if (p->plts_eaten == p->plts_max)
			break ;
	}
	if (!did_i_died(p))
		regular_status_out(p, "is out");
	return (NULL);
}
