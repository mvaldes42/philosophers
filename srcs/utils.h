/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:46:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 12:14:53 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

void		exit_failure(t_innkeper *innkeeper);
void		exit_success(t_innkeper *innkeeper);
long int	from_time_to_ms(struct timeval what_time);
void		talk(pthread_mutex_t *talk_lock, char *speech, int x);
void		talk_two(pthread_mutex_t *talk_lock, char *speech, int x, int y);

#endif