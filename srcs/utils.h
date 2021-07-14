/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:46:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 18:47:34 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

void		exit_success(t_innkeper *innkeeper);
long int	from_time_to_ms(struct timeval what_time);
void		regular_status_out(t_philo *p, char *str);
void		death_status_out(t_philo *p);

void		say_status(char *str, int id, struct timeval start);
void		say_status_nb(char *str, int id, int nb, struct timeval start);
void		say_death_status(int id, struct timeval start, \
			struct timeval lst_eat);
int			did_else_died(t_shared_in *s_in);
int			did_i_died(t_philo *p);
void		ft_usleep(long int max_time);
void		ft_putstr(char *s);
void		ft_putnbr(int n);
#endif