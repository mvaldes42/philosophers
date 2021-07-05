/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/05 18:08:21 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*myThreadFun(void *vargp)
{
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_id;
	pthread_t	thread_id_2;

	printf("Before Thread 1\n");
	pthread_create(&thread_id, NULL, myThreadFun, NULL);
	pthread_join(thread_id, NULL);
	printf("After Thread 1\n");
	printf("Before Thread 2\n");
	pthread_create(&thread_id_2, NULL, myThreadFun, NULL);
	pthread_join(thread_id_2, NULL);
	printf("After Thread 2\n");
	exit(0);
}
