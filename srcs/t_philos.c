/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:50:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 15:23:29 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	init_philo(t_philo *p)
{
	p->r_frk_id = p->p_id - 1;
	p->l_frk_id = p->p_id;
	p->plts_max = p->inputs->plts_p_philo;
	p->is_even = p->p_id % 2;
	p->alive = 1;
	gettimeofday(&p->lst_meal, NULL);
	pthread_mutex_lock(&p->s_in->state_lck[p->p_id]);
	p->eating = 0;
	pthread_mutex_unlock(&p->s_in->state_lck[p->p_id]);
}

static void	circle_states(t_philo	*p)
{
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_eat(p);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_sleep(p);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_think(p);
}

static void	smol_circle_states(t_philo	*p)
{
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_think(p);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_eat(p);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_sleep(p);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		p_think(p);
}

void	*philosopher(void *philosoher)
{
	t_philo	*p;

	p = (t_philo *)philosoher;
	init_philo(p);
	if (p->r_frk_id == 0)
	{
		p->r_frk_id = p->inputs->nb_p;
	}
	while (p->alive == 1 && p->plts_eaten < p->plts_max)
	{
		if (p->plts_eaten == 0 && p->is_even == 0)
			circle_states(p);
		else if (p->plts_eaten == 0 && p->is_even == 1)
			smol_circle_states(p);
		else if (p->plts_eaten != 0 && p->plts_eaten < p->plts_max && \
		p->alive == 1)
			circle_states(p);
	}
	if (p->alive)
		printf("#%d DONE\n", p->p_id);
	return (NULL);
}