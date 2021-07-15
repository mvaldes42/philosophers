/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/15 14:56:26 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	regular_status_out(t_philo *p, char *str)
{
	int				x;

	pthread_mutex_lock(&p->s_in->talk_lock);
	x = time_diff_ms(p->in->start_time);
	printf("%4d -> %d %s\n", x, p->p_id, str);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

void	death_status_out(t_philo *p)
{
	int				x;
	int				last_meal;

	pthread_mutex_lock(&p->s_in->talk_lock);
	last_meal = time_diff_ms(p->lst_meal);
	x = time_diff_ms(p->in->start_time);
	printf("%4d -> %d is dead after %dms\n", x, p->p_id, last_meal);
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

long int	time_diff_ms(struct timeval	time_compare)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (from_time_to_ms(current_time) - from_time_to_ms(time_compare));
}
