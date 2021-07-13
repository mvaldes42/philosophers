/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 10:25:18 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_failure(t_innkeper *innkeeper)
{
	if (innkeeper->p)
		free(innkeeper->p);
	exit(EXIT_FAILURE);
}

void	exit_success(t_innkeper *innkeeper)
{
	if (innkeeper->p)
		free(innkeeper->p);
	exit(EXIT_SUCCESS);
}

long int	from_time_to_ms(struct timeval what_time)
{
	long int	ms;

	ms = what_time.tv_sec * 1000 + what_time.tv_usec / 1000;
	return (ms);
}

void	talk_2(t_philo *p, char *str, struct timeval time, int id)
{
	pthread_mutex_lock(&p->s_in->talk_lock);
	printf(str, \
	from_time_to_ms(time) - from_time_to_ms(p->inputs->sim_start_time), id);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}

void	talk_3(t_philo *p, char *str, struct timeval time, int id, int nb)
{
	pthread_mutex_lock(&p->s_in->talk_lock);
	printf(str, \
	from_time_to_ms(time) - from_time_to_ms(p->inputs->sim_start_time), id, nb);
	pthread_mutex_unlock(&p->s_in->talk_lock);
}
