/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:52:26 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/20 12:19:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static int	args_are_valid(int argc, char **argv, t_innkeper *inn, t_inputs *in)
{
	if (argc <= 4)
		return (0);
	if (strchr(argv[1], '.') || strchr(argv[2], '.') || strchr(argv[3], '.') \
	|| strchr(argv[4], '.') || \
	strchr(argv[1], ',') || strchr(argv[2], ',') || strchr(argv[3], ',') \
	|| strchr(argv[4], ','))
		return (0);
	if (argc == 6 && (strchr(argv[5], ',') || strchr(argv[5], '.')))
		return (0);
	return (1);
}

static int	imputs_are_valid(t_inputs *in)
{
	if (in->nb_p < 1 || in->time_die <= 0 || in->time_eat < 0 || \
	in->time_sleep < 0 || in->plts_p_philo <= 0)
		return (0);
	return (1);
}

static void	parse_inputs(int argc, char **argv, t_innkeper *inn, t_inputs *in)
{
	gettimeofday(&inn->in_ptr.start_time, NULL);
	in->nb_p = (int)ft_atoi(argv[1]);
	in->time_die = (int)ft_atoi(argv[2]);
	in->time_eat = (int)ft_atoi(argv[3]);
	in->time_sleep = (int)ft_atoi(argv[4]);
	if (argc == 6)
		in->plts_p_philo = ft_atoi(argv[5]);
	else
		in->plts_p_philo = __LONG_LONG_MAX__;
	if (in->nb_p % 2 == 1)
		in->time_thk = in->time_eat * 2 - in->time_sleep;
	else
		in->time_thk = in->time_eat - in->time_sleep;
	inn->in_ptr.plts_tot = inn->in_ptr.plts_p_philo * inn->in_ptr.nb_p;
}

int	init_inputs(int argc, char **argv, t_innkeper *inn)
{
	t_inputs	*inputs;
	int			i;

	inputs = &inn->in_ptr;
	memset(inputs, 0, sizeof(*inputs));
	memset(&inn->s_in, 0, sizeof(inn->s_in));
	memset(&inputs->start_time, 0, sizeof(struct timeval));
	if (!args_are_valid(argc, argv, inn, inputs))
		return (0);
	parse_inputs(argc, argv, inn, inputs);
	if (!imputs_are_valid(inputs))
		return (0);
	inn->p = malloc(inn->in_ptr.nb_p * sizeof(t_philo));
	i = 0;
	while (i < inn->in_ptr.nb_p)
	{
		memset(&inn->p[i], 0, sizeof(t_philo));
		i++;
	}
	return (1);
}
