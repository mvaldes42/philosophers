/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 14:28:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

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

void	say_status(char *str, int id, struct timeval start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_putnbr(from_time_to_ms(time) - from_time_to_ms(start));
	ft_putstr("  >>");
	ft_putstr(" ");
	ft_putnbr(id);
	ft_putstr(" ");
	ft_putstr(str);
	ft_putstr("\n");
}

void	say_status_nb(char *str, int id, int nb, struct timeval start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_putnbr(from_time_to_ms(time) - from_time_to_ms(start));
	ft_putstr("  >>");
	ft_putstr(" ");
	ft_putnbr(id);
	ft_putstr(" ");
	ft_putstr(str);
	ft_putstr(" ");
	ft_putnbr(nb);
	ft_putstr("\n");
}
