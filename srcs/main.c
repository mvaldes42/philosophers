/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/12 14:46:33 by mvaldes          ###   ########.fr       */
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

static void	init_mutexs(t_innkeper *inn)
{
	int	i;

	i = 1;
	while (i <= inn->in_ptr.nb_p)
	{
		pthread_mutex_init(&inn->s_in.frk_lck[i], NULL);
		pthread_mutex_init(&inn->s_in.state_lck[i], NULL);
		if (i <= floor(inn->in_ptr.nb_p / 2))
			pthread_mutex_init(&inn->s_in.plts_lck[i], NULL);
		i++;
	}
	pthread_mutex_init(&inn->s_in.talk_lock, NULL);
}

static void	init_threads(t_innkeper *inn)
{
	int	i;

	i = 1;
	pthread_create(&inn->death_clock, NULL, are_philo_dead, (void *)inn);
	while (i <= inn->in_ptr.nb_p)
	{
		memset(&inn->p[i], 0, sizeof(inn->p[i]));
		inn->p[i].p_id = i;
		inn->p[i].inputs = &inn->in_ptr;
		inn->p[i].s_in = &inn->s_in;
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
	// pthread_join(inn->death_clock, NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	init_inputs(argc, argv, &inn);
	init_mutexs(&inn);
	init_threads(&inn);
	close_threads(&inn);
	// i = 1;
	// while (i <= inn.in_ptr.nb_p)
	// {
	// 	pthread_mutex_init(&inn.s_in.frk_lck[i], NULL);
	// 	pthread_mutex_init(&inn.s_in.state_lck[i], NULL);
	// 	if (i <= floor(inn.in_ptr.nb_p / 2))
	// 		pthread_mutex_init(&inn.s_in.plts_lck[i], NULL);
	// 	i++;
	// }
	// pthread_mutex_init(&inn.s_in.talk_lock, NULL);
	// i = 1;
	// pthread_create(&inn.death_clock, NULL, are_philo_dead, (void *)&inn);
	// while (i <= inn.in_ptr.nb_p)
	// {
	// 	memset(&inn.p[i], 0, sizeof(inn.p[i]));
	// 	inn.p[i].p_id = i;
	// 	inn.p[i].inputs = &inn.in_ptr;
	// 	inn.p[i].s_in = &inn.s_in;
	// 	pthread_create(&inn.p[i].t_id, NULL, philosopher, (void *)&inn.p[i]);
	// 	i++;
	// }
	// i = 1;
	// while (i <= inn.in_ptr.nb_p)
	// {
	// 	pthread_join(inn.p[i].t_id, NULL);
	// 	i++;
	// }
	exit_success(&inn);
}
