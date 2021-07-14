/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 19:03:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	regular_status_out(t_philo *p, char *str)
{
	struct timeval	time;
	int				x;

	pthread_mutex_lock(&p->s_in->talk_lock);
	gettimeofday(&time, NULL);
	x = from_time_to_ms(time) - from_time_to_ms(p->in->start_time);
	printf("%-4d >> %d %s\n", x, p->p_id, str);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

void	death_status_out(t_philo *p)
{
	struct timeval	time;
	int				x;
	int				last_meal;

	pthread_mutex_lock(&p->s_in->talk_lock);
	gettimeofday(&time, NULL);
	last_meal = from_time_to_ms(time) - from_time_to_ms(p->lst_meal);
	x = from_time_to_ms(time) - from_time_to_ms(p->in->start_time);
	printf("%-4d >> %d is dead after %dms\n", x, p->p_id, last_meal);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

int	did_else_died(t_shared_in *s_in)
{
	int	someone_is_dead;

	pthread_mutex_lock(&s_in->someone_died_lock);
	someone_is_dead = s_in->someone_died;
	pthread_mutex_unlock(&s_in->someone_died_lock);
	if (someone_is_dead == 1)
		return (1);
	return (0);
}

int	did_i_died(t_philo *p)
{
	int	i_am_alive;

	pthread_mutex_lock(&p->alive_lock);
	i_am_alive = p->alive;
	pthread_mutex_unlock(&p->alive_lock);
	if (i_am_alive == 1)
		return (0);
	return (1);
}
