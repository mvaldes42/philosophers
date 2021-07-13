/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:52:26 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 14:10:13 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

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
		in->plts_p_philo = -1;
	in->time_thk = in->time_eat;
	inn->in_ptr.plts_tot = inn->in_ptr.plts_p_philo * inn->in_ptr.nb_p;
}

void	init_inputs(int argc, char **argv, t_innkeper *inn)
{
	t_inputs	*inputs;

	if (argc < 4)
		exit_failure(inn);
	inputs = &inn->in_ptr;
	memset(inputs, 0, sizeof(*inputs));
	memset(&inn->s_in, 0, sizeof(inn->s_in));
	inn->p = malloc((inn->in_ptr.nb_p + 1) * sizeof(inn->p));
	inn->s_in.plts_lck = malloc((floor(inn->in_ptr.nb_p / 2) + 1) \
	* sizeof(inn->s_in.plts_lck));
	parse_inputs(argc, argv, inn, inputs);
}
