/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:20 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/09 15:45:31 by mvaldes          ###   ########.fr       */
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
# include <stdarg.h>

typedef enum e_actions
{
	TAKING_A_FORK,
	EATING,
	DROPING_FORKS,
	SLEEPING,
	THINKING,
}	t_actions;

typedef struct s_shared_inputs
{
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	plates_lock;
	pthread_mutex_t	talk_lock;
	int				nb_total_meals_eaten;
}	t_shared_in;

typedef struct s_inputs
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_think;
	int			nb_plates_per_philo;
	int			nb_plates_total;
}	t_inputs;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	t_inputs		*inputs;
	t_shared_in		*shared_in;
	int				am_i_even;
	int				right_fork_id;
	int				left_fork_id;
	struct timeval	time_since_last_meal;
	int				nb_plates_eaten;
	int				nb_plates_allowed;
	bool			is_alive;
}	t_philo;

typedef struct s_innkeeper
{
	t_inputs		in_ptr;
	t_philo			*philo;
	t_shared_in		shared_in;
	pthread_t		death_clock;
	struct timeval	current_time;
}	t_innkeper;

char	**ft_split(char const *s, char c);
int		word_count(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strdup(const char *s1);
void	exit_failure(t_innkeper *innkeeper);
void	exit_success(t_innkeper *innkeeper);

#endif