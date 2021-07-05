/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:37:13 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/05 18:51:38 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// milliseconds = microseconds ÷ 1,000
// struct object{
//         int data;
//         void (*new_func) (int * data);
// };

// void scan_data (int * data) {
//         printf(" input : ");
//         scanf("%d", data);
// }

// struct object f;
// f.new_func = scan_data;
// f.new_func(&f.data);

void	*myThreadFun(void *input)
{
	sleep(1);
	int *myid = (int *)input;
	printf("Printing GeeksQuiz from Thread %d\n", (int*)myid);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_id;
	pthread_t	thread_id_2;

	printf("Before Thread 1\n");
	pthread_create(&thread_id, NULL, myThreadFun, (void*)&thread_id);
	printf("After Thread 1\n");
	printf("Before Thread 2\n");
	pthread_create(&thread_id_2, NULL, myThreadFun, (void*)&thread_id_2);
	printf("After Thread 2\n");
	pthread_join(thread_id, NULL);
	pthread_join(thread_id_2, NULL);
	exit(0);
}
