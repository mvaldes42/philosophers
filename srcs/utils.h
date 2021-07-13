/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:46:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 14:59:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

void		exit_failure(t_innkeper *innkeeper);
void		exit_success(t_innkeper *innkeeper);
long int	from_time_to_ms(struct timeval what_time);
void		say_status(char *str, int id, struct timeval start);
void		say_status_nb(char *str, int id, int nb, struct timeval start);
void		ft_usleep(long int max_time);
void		ft_putstr(char *s);
void		ft_putnbr(int n);
#endif