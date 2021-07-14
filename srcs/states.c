/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:48:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 16:52:15 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

// say_status_nb("take left fork", p->p_id, p->l_frk_id, p->in->start_time);
// say_status_nb("take right fork", p->p_id, p->r_frk_id, p->in->start_time);
// say_status_nb("down left fork", p->p_id, p->l_frk_id, p->in->start_time);
// say_status_nb("down right fork", p->p_id, p->r_frk_id, p->in->start_time);

static void	eating_lock(t_philo *p)
{
	pthread_mutex_lock(&p->left_lock);
	pthread_mutex_lock(p->right_lock);
	pthread_mutex_lock(&p->s_in->talk_lock);
	say_status("take forks", p->p_id, p->in->start_time);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

static void	eating_unlock(t_philo *p)
{
	if (!did_p_died(p->s_in))
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status("down forks", p->p_id, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
	}
	pthread_mutex_unlock(&p->left_lock);
	pthread_mutex_unlock(p->right_lock);
}

// printf("%d plts\n", p->plts_eaten);

int	p_eat(t_philo *p)
{
	int				x;
	struct timeval	time;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x > p->in->time_die)
	{
		p->alive = 0;
		return (0);
	}
	else
	{
		eating_lock(p);
		gettimeofday(&p->lst_meal, NULL);
		pthread_mutex_lock(&p->plts_lock);
		p->plts_eaten++;
		pthread_mutex_unlock(&p->plts_lock);
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status("is eating", p->p_id, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
		ft_usleep(p->in->time_eat);
		eating_unlock(p);
	}
	return (1);
}

int	p_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->s_in->talk_lock);
	say_status("is sleeping", p->p_id, p->in->start_time);
	pthread_mutex_unlock(&p->s_in->talk_lock);
	ft_usleep(p->in->time_sleep);
	return (1);
}

int	p_think(t_philo *p)
{
	struct timeval	time;
	int				x;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x > p->in->time_die)
	{
		p->alive = 0;
		return (0);
	}
	else if (p->alive == 1 && p->plts_eaten < p->plts_max)
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status("is thinking", p->p_id, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
	}
	return (1);
}
