/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:31:31 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 18:52:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_success(t_innkeper *innkeeper)
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
	long int		pass_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	start_time = from_time_to_ms(time);
	pass_time = start_time;
	while ((pass_time - start_time) < max_time)
	{
		gettimeofday(&time, NULL);
		pass_time = from_time_to_ms(time);
		usleep(max_time / 10);
	}
}
