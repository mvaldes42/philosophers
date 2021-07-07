/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:20 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/07 10:36:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>

typedef enum e_actions
{
	TAKING_A_FORK,
	EATING,
	DROPING_FORKS,
	SLEEPING,
	THINKING,
}	t_actions;

typedef struct s_inputs
{
	struct timeval	current_time;
	long int		start_sim_ms;
	long int		current_ms;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_plates;
	pthread_mutex_t	*forks;
	t_actions		*actions;
	pthread_mutex_t	meals_lock;
	int				nb_meals_eaten;
	int				nb_meals_tot;
}	t_inputs;

typedef struct s_philo
{
	int			philo_id;
	pthread_t	thread_id;
	t_inputs	*inputs;
	int			right_fork_id;
	int			left_fork_id;
	bool		right_fork_locked;
	bool		left_fork_locked;
	t_actions	current_action;
	signed int	time_start_of_action;
	char		*current_status;
	signed int	time_status_printed;
	signed int	timer_to_next;
	int			priority_to_eat;
	signed int	time_since_last_meal;
	int			number_of_meals_eaten;
	bool		is_alive;
	int			erno;
}	t_philo;

typedef struct s_innkeeper
{
	t_inputs		in_ptr;
	t_philo			*philo;
}	t_innkeper;

char	**ft_split(char const *s, char c);
int		word_count(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strdup(const char *s1);
void	exit_failure(t_innkeper *innkeeper);
void	exit_success(t_innkeper *innkeeper);

#endif