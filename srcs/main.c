/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/20 19:57:43 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	init_mutexs(t_innkeper *inn)
{
	int	i;

	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		pthread_mutex_init(&inn->p[i].left_lock, NULL);
		pthread_mutex_init(&inn->p[i].alive_lock, NULL);
		pthread_mutex_init(&inn->p[i].plts_lock, NULL);
		i++;
	}
	pthread_mutex_init(&inn->s_in.talk_lock, NULL);
	pthread_mutex_init(&inn->s_in.smne_d_lock, NULL);
	pthread_mutex_init(&inn->s_in.plts_e_tot_lock, NULL);
}

static void	create_threads(t_innkeper *inn)
{
	long long	i;

	i = 0;
	pthread_create(&inn->death_clock, NULL, death_check_t, (void *)inn);
	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		inn->p[i].p_id = i;
		inn->p[i].in = &inn->in_ptr;
		inn->p[i].s_in = &inn->s_in;
		if (i == 0)
			inn->p[i].right_lock = &inn->p[inn->in_ptr.nb_p - 1].left_lock;
		else
			inn->p[i].right_lock = &inn->p[i - 1].left_lock;
		pthread_create(&inn->p[i].t_id, NULL, philo_t, (void *)&inn->p[i]);
		i++;
	}
}

static void	close_threads(t_innkeper *inn)
{
	int	i;

	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		pthread_join(inn->p[i].t_id, NULL);
		i++;
	}
	pthread_join(inn->death_clock, NULL);
}

static void	destroy_mutexts(t_innkeper *inn)
{
	int	i;

	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		pthread_mutex_destroy(&inn->p[i].left_lock);
		pthread_mutex_destroy(&inn->p[i].plts_lock);
		pthread_mutex_destroy(&inn->p[i].alive_lock);
		i++;
	}
	pthread_mutex_destroy(&inn->s_in.talk_lock);
	pthread_mutex_destroy(&inn->s_in.smne_d_lock);
	pthread_mutex_destroy(&inn->s_in.plts_e_tot_lock);
}

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	if (!init_inputs(argc, argv, &inn))
		return (0);
	init_mutexs(&inn);
	create_threads(&inn);
	close_threads(&inn);
	destroy_mutexts(&inn);
	free_philo(&inn);
	return (1);
}
