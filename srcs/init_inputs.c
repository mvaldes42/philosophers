/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:52:26 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/20 11:26:05 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	exit_failure(t_innkeper *inn)
{
	exit(EXIT_SUCCESS);
}

static void	args_are_valid(int argc, char **argv, t_innkeper *inn, t_inputs *in)
{
	if (argc <= 4)
		exit_failure(inn);
	if (strchr(argv[1], '.') || strchr(argv[2], '.') || strchr(argv[3], '.') \
	|| strchr(argv[4], '.') || \
	strchr(argv[1], ',') || strchr(argv[2], ',') || strchr(argv[3], ',') \
	|| strchr(argv[4], ','))
		exit_failure(inn);
	if (argc == 6 && (strchr(argv[5], ',') || strchr(argv[5], '.')))
		exit_failure(inn);
}

static void	parse_inputs(int argc, char **argv, t_innkeper *inn, t_inputs *in)
{
	gettimeofday(&inn->in_ptr.start_time, NULL);
	in->nb_p = atoi(argv[1]);
	in->time_die = atoi(argv[2]);
	in->time_eat = atoi(argv[3]);
	in->time_sleep = atoi(argv[4]);
	if (argc == 6)
		in->plts_p_philo = atoi(argv[5]);
	else
		in->plts_p_philo = __LONG_LONG_MAX__;
	if (in->nb_p % 2 == 1)
		in->time_thk = in->time_eat * 2 - in->time_sleep;
	else
		in->time_thk = in->time_eat - in->time_sleep;
	inn->in_ptr.plts_tot = inn->in_ptr.plts_p_philo * inn->in_ptr.nb_p;
	if (in->nb_p < 1 || in->time_die <= 0 || in->time_eat < 0 || \
	in->time_sleep < 0 || in->plts_p_philo <= 0)
		exit_failure(inn);
}

void	init_inputs(int argc, char **argv, t_innkeper *inn)
{
	t_inputs	*inputs;
	int			i;

	inputs = &inn->in_ptr;
	memset(inputs, 0, sizeof(*inputs));
	memset(&inn->s_in, 0, sizeof(inn->s_in));
	args_are_valid(argc, argv, inn, inputs);
	parse_inputs(argc, argv, inn, inputs);
	inn->p = malloc(inn->in_ptr.nb_p * sizeof(t_philo));
	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		memset(&inn->p[i], 0, sizeof(t_philo));
		i++;
	}
}
