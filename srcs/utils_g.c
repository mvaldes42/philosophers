/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:31:31 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/20 12:23:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_philo(t_innkeper *innkeeper)
{
	if (innkeeper->p)
		free(innkeeper->p);
}

long int	from_time_to_ms(struct timeval what_time)
{
	long int	ms;

	ms = what_time.tv_sec * 1000 + what_time.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(long int max_time)
{
	long int		start_time;
	long int		current_time;
	struct timeval	time;

	memset(&time, 0, sizeof(struct timeval));
	gettimeofday(&time, NULL);
	start_time = from_time_to_ms(time);
	current_time = start_time;
	while ((current_time - start_time) < max_time)
	{
		gettimeofday(&time, NULL);
		current_time = from_time_to_ms(time);
		usleep(max_time / 10);
	}
}

void	ft_usleep_states(long int max_time, t_philo *p)
{
	long int		start_time;
	long int		current_time;
	struct timeval	time;

	memset(&time, 0, sizeof(struct timeval));
	gettimeofday(&time, NULL);
	start_time = from_time_to_ms(time);
	current_time = start_time;
	while (((current_time - start_time) < max_time) && \
	(!did_e_died(p->s_in) && !did_i_died(p)))
	{
		gettimeofday(&time, NULL);
		current_time = from_time_to_ms(time);
		usleep(10);
	}
}

long int	time_diff_ms(struct timeval	time_compare)
{
	struct timeval	current_time;

	memset(&current_time, 0, sizeof(struct timeval));
	gettimeofday(&current_time, NULL);
	return (from_time_to_ms(current_time) - from_time_to_ms(time_compare));
}
