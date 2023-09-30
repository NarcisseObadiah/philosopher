/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:32:28 by mobadiah          #+#    #+#             */
/*   Updated: 2023/09/30 12:34:32 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <pthread.h>
#include <unistd.h>

void	*routine(void *arg)
{
	(void)arg;
	printf("Threads start\n");
	sleep(3);
	printf("ending threads\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, routine, NULL) != 0)
	{
		return (2);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}	
