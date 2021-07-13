/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 14:33:48 by mvaldes          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int			i;
	t_innkeper	inn;

	memset(&inn, 0, sizeof(inn));
	init_inputs(argc, argv, &inn);
	init_mutexs(&inn);
	init_threads(&inn);
	close_threads(&inn);
	exit_success(&inn);
}

// typedef struct s_philoter
// {
// 	pthread_mutex_t	mutex_gauche;
// 	pthread_mutex_t	*mutex_droite;
// 	int				p_id;
// 	pthread_t		thread_id;

// }	t_philoter;

// typedef struct s_data
// {
// 	t_philoter	*philo;
// }	t_data;

// void	*philo_thread(void *pp)
// {
// 	char		*str;
// 	int			i;
// 	t_philoter	*philou;

// 	i = 0;
// 	philou = (t_philoter *)pp;
// 	str = "tread 1 : coucou ca va ? \n";
// 	pthread_mutex_lock(&philou->mutex_gauche);
// 	pthread_mutex_lock(philou->mutex_droite);
// 	printf("%d lock\n", philou->p_id);
// 	while (str[i])
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// 	printf("%d unlock\n", philou->p_id);
// 	pthread_mutex_unlock(&philou->mutex_gauche);
// 	pthread_mutex_unlock(philou->mutex_droite);
// 	return (NULL);
// }

// int	main(void)
// {
// 	t_data		data;
// 	int			i;
// 	int			nb_philo;

// 	nb_philo = 2;
// 	data.philo = malloc((2 + 1) * sizeof(data.philo));
// 	i = 1;
// 	while (i <= nb_philo)
// 	{
// 		pthread_mutex_init(&data.philo[i].mutex_gauche, NULL);
// 		if (i - 1 == 0)
// 			data.philo[i].mutex_droite = &data.philo[nb_philo].mutex_gauche;
// 		else
// 			data.philo[i].mutex_droite = &data.philo[i - 1].mutex_gauche;
// 		data.philo[i].p_id = i;
// 		pthread_create(&data.philo[i].thread_id, NULL, philo_thread, (void *)&data.philo[i]);
// 		i++;
// 	}
// 	// i = 1;
// 	// while (i <= nb_philo)
// 	// {
// 	// 	pthread_join(&data.philo[i], NULL);
// 	// 	i++;
// 	// }
// 	sleep(1);
// }
