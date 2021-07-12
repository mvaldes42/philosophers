/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 13:07:09 by mvaldes          ###   ########.fr       */
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

void	talk(pthread_mutex_t *talk_lock, char *speech, int x)
{
	pthread_mutex_lock(talk_lock);
	printf(speech, x);
	pthread_mutex_unlock(talk_lock);
}

void	talk_two(pthread_mutex_t *talk_lock, char *speech, int x, int y)
{
	pthread_mutex_lock(talk_lock);
	printf(speech, x, y);
	pthread_mutex_unlock(talk_lock);
}
