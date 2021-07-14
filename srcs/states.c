/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:48:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 14:53:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	eating_lock(t_philo *p)
{
	pthread_mutex_lock(&p->left_lock);
	pthread_mutex_lock(p->right_lock);
	pthread_mutex_lock(&p->s_in->talk_lock);
	say_status("take forks", p->p_id, p->in->start_time);
	// say_status_nb("take left fork", p->p_id, p->l_frk_id, p->in->start_time);
	// say_status_nb("take right fork", p->p_id, p->r_frk_id, p->in->start_time);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

static void	eating_unlock(t_philo *p)
{
	pthread_mutex_lock(&p->s_in->talk_lock);
	say_status("down forks", p->p_id, p->in->start_time);
	// say_status_nb("down left fork", p->p_id, p->l_frk_id, p->in->start_time);
	// say_status_nb("down right fork", p->p_id, p->r_frk_id, p->in->start_time);
	pthread_mutex_unlock(&p->s_in->talk_lock);
	pthread_mutex_unlock(&p->left_lock);
	pthread_mutex_unlock(p->right_lock);
}

void	p_eat(t_philo *p)
{
	int				x;
	struct timeval	time;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x > p->in->time_die)
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_death_status(p->p_id, p->in->start_time, p->lst_meal);
		pthread_mutex_unlock(&p->s_in->talk_lock);
		p->alive = 0;
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
		printf("%d plts\n", p->plts_eaten);
		pthread_mutex_unlock(&p->s_in->talk_lock);
		ft_usleep(p->in->time_eat);
		eating_unlock(p);
	}
}

void	p_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->s_in->talk_lock);
	say_status("is sleeping", p->p_id, p->in->start_time);
	pthread_mutex_unlock(&p->s_in->talk_lock);
	ft_usleep(p->in->time_sleep);
}

void	p_think(t_philo *p)
{
	struct timeval	time;
	int				x;

	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	if (x > p->in->time_die)
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_death_status(p->p_id, p->in->start_time, p->lst_meal);
		pthread_mutex_unlock(&p->s_in->talk_lock);
		p->alive = 0;
		exit(EXIT_SUCCESS);
	}
	else if (p->alive == 1 && p->plts_eaten < p->plts_max)
	{
		pthread_mutex_lock(&p->s_in->talk_lock);
		say_status("is thinking", p->p_id, p->in->start_time);
		pthread_mutex_unlock(&p->s_in->talk_lock);
	}
}
