/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 17:18:40 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	exit_failure(t_innkeper *inn)
{
	if (inn->p)
		free(inn->p);
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

void	say_death_status(int id, struct timeval start, struct timeval lst_eat)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_putnbr(from_time_to_ms(time) - from_time_to_ms(start));
	ft_putstr("  >>");
	ft_putstr(" ");
	ft_putnbr(id);
	ft_putstr(" /!\\ IS DEAD /!\\ ");
	ft_putnbr(from_time_to_ms(time) - from_time_to_ms(lst_eat));
	ft_putstr("\n");
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
