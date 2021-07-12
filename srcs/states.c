/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:48:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 15:30:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	eating_lock(t_philo *p)
{
	pthread_mutex_lock(&p->s_in->frk_lck[p->r_frk_id]);
	pthread_mutex_lock(&p->s_in->frk_lck[p->l_frk_id]);
	pthread_mutex_lock(&p->s_in->plts_lck[0]);
	pthread_mutex_lock(&p->s_in->state_lck[p->p_id]);
	p->eating = 1;
	pthread_mutex_unlock(&p->s_in->state_lck[p->p_id]);
}

static void	eating_unlock(t_philo *p)
{
	pthread_mutex_unlock(&p->s_in->plts_lck[0]);
	pthread_mutex_unlock(&p->s_in->frk_lck[p->r_frk_id]);
	pthread_mutex_unlock(&p->s_in->frk_lck[p->l_frk_id]);
	pthread_mutex_lock(&p->s_in->state_lck[p->p_id]);
	p->eating = 0;
	pthread_mutex_unlock(&p->s_in->state_lck[p->p_id]);
}
// pthread_mutex_lock(&p->s_in->talk_lock);
// printf("#%d eat delay is = %d, time to die = %d\n", \
p->p_id, x, p->inputs->time_die);
// pthread_mutex_unlock(&p->s_in->talk_lock);

void	p_eat(t_philo *p)
{
	struct timeval	c_time;
	struct timeval	time;
	int				x;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x >= p->inputs->time_die)
	{
		p->alive = 0;
		usleep(10 * 1000);
	}
	else
	{
		eating_lock(p);
		gettimeofday(&p->lst_meal, NULL);
		p->s_in->tot_plts_eaten++;
		p->plts_eaten++;
		talk_two(&p->s_in->talk_lock, "#%d is eating, he ate %d plates,\n", \
		p->p_id, p->plts_eaten);
		usleep(p->inputs->time_eat * 1000);
		talk(&p->s_in->talk_lock, "#%d forks down\n", p->p_id);
		eating_unlock(p);
	}
}

void	p_sleep(t_philo *p)
{
	talk(&p->s_in->talk_lock, "#%d is sleeping\n", p->p_id);
	usleep(p->inputs->time_sleep * 1000);
}

void	p_think(t_philo *p)
{
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		talk(&p->s_in->talk_lock, "#%d is thinking\n", p->p_id);
}
