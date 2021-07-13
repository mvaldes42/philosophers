/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:48:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 10:25:58 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	eating_lock(t_philo *p)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&p->s_in->frk_lck[p->r_frk_id]);
	talk_3(p, "%-4d >> #%d take right fork %d\n", time , p->p_id, p->r_frk_id);
	pthread_mutex_lock(&p->s_in->frk_lck[p->l_frk_id]);
	talk_3(p, "%-4d >> #%d take left fork %d\n", time, p->p_id, p->l_frk_id);
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
	struct timeval	time;
	int				x;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x >= p->inputs->time_die)
	{
		p->alive = 0;
		// printf("p #%d x = %d, ttd = %d\n", p->p_id, x, p->inputs->time_die);
		// talk(&p->s_in->talk_lock, "#%d is deadddd\n", p->p_id);
		// exit(EXIT_SUCCESS);
	}
	else
	{
		eating_lock(p);
		gettimeofday(&p->lst_meal, NULL);
		p->s_in->tot_plts_eaten++;
		p->plts_eaten++;
		gettimeofday(&time, NULL);
		talk_3(p, "%-4d >> #%d is eating, he ate %d plates,\n", time, p->p_id, p->plts_eaten);
		usleep(p->inputs->time_eat * 1000);
		gettimeofday(&time, NULL);
		talk_2(p, "%-4d >> #%d forks down\n", time, p->p_id);
		eating_unlock(p);
	}
}

void	p_sleep(t_philo *p)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	talk_2(p, "%-4d >> #%d is sleeping\n", time, p->p_id);
	usleep(p->inputs->time_sleep * 1000);
}

void	p_think(t_philo *p)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (p->alive == 1 && p->plts_eaten < p->plts_max)
		talk_2(p, "%-4d >> #%d is thinking\n", time, p->p_id);
}
