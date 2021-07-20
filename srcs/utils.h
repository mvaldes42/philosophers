/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:46:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/20 11:48:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

long long	ft_atoi(const char *str);

void		exit_success(t_innkeper *innkeeper);
long int	from_time_to_ms(struct timeval what_time);
void		ft_usleep(long int max_time);
void		ft_usleep_states(long int max_time, t_philo *p);
long int	time_diff_ms(struct timeval	time_compare);

void		regular_status_out(t_philo *p, char *str);
void		eating_status_out(t_philo *p, char *str);
void		death_status_out(t_philo *p);
int			did_e_died(t_shared_in *s_in);
int			did_i_died(t_philo *p);
#endif