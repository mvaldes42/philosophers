/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/14 18:01:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

//4 410 200 200
// 5 800 200 200
// 4 310 200 100 (mort)
// Avec 2 philosophes seulement pour tester le delai d'affichage de la mort
// ya aussi 5 800 200 200 7
// et 1 800 200 200 (depuis recemment)

static void	create_threads(t_innkeper *inn)
{
	long long	i;

	i = 1;
	pthread_create(&inn->death_clock, NULL, are_philo_dead, (void *)inn);
	while (i <= inn->in_ptr.nb_p)
	{
		memset(&inn->p[i], 0, sizeof(inn->p[i]));
		inn->p[i].p_id = i;
		inn->p[i].in = &inn->in_ptr;
		inn->p[i].s_in = &inn->s_in;
		pthread_mutex_init(&inn->p[i].left_lock, NULL);
		if (i - 1 == 0)
			inn->p[i].right_lock = &inn->p[inn->in_ptr.nb_p].left_lock;
		else
			inn->p[i].right_lock = &inn->p[i - 1].left_lock;
		pthread_create(&inn->p[i].t_id, NULL, philosopher, (void *)&inn->p[i]);
		i++;
	}
}

static void	close_threads(t_innkeper *inn)
{
	int	i;

	i = 1;
	while (i <= inn->in_ptr.nb_p)
	{
		pthread_join(inn->p[i].t_id, NULL);
		i++;
	}
}

static void	destroy_mutexts(t_innkeper *inn)
{
	int	i;

	i = 1;
	while (i <= inn->in_ptr.nb_p)
	{
		pthread_mutex_destroy(&inn->p[i].left_lock);
		pthread_mutex_destroy(&inn->p[i].plts_lock);
		pthread_mutex_destroy(&inn->p[i].alive_lock);
		i++;
	}
	pthread_mutex_destroy(&inn->s_in.talk_lock);
}

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	init_inputs(argc, argv, &inn);
	pthread_mutex_init(&inn.s_in.talk_lock, NULL);
	create_threads(&inn);
	close_threads(&inn);
	destroy_mutexts(&inn);
	exit_success(&inn);
	exit(EXIT_SUCCESS);
}
