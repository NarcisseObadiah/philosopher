/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 06:29:55 by mobadiah         #+#    #+#             */
/*   Updated: 2023/10/06 14:33:59 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	init_mutex(t_philo *ph)
{
	pthread_mutex_init(&ph->data.mutex_write, NULL);
	pthread_mutex_init(&ph->data.mutex_dead, NULL);
	pthread_mutex_init(&ph->data.mutex_time_eat, NULL);
	pthread_mutex_init(&ph->data.mutex_end, NULL);
}
/* This fucntion specificaly launch each philo with a left fork
   and the right fork of each philo is the left fork of the nereby philo
   also the starting time, the philo eating_status and the number 
   of philo are initialize */

int	init_data(t_philo *ph)
{
	int	index;

	index = 0;
	ph->data.starting_time = time_now();
	ph->data.status = 0;
	ph->data.num_phil_finished = 0;
	init_mutex(ph);
	while (index < ph->data.nb_of_philos)
	{
		ph->philo[index].id = index + 1;
		ph->philo[index].last_eat_time = ph->data.starting_time;
		ph->philo[index].num_eat = 0;
		ph->philo[index].end = 0;
		ph->philo[index].right_fork = NULL;
		pthread_mutex_init(&ph->philo[index].left_fork, NULL);
		if (ph->data.nb_of_philos == 1)
			return (1);
		if (index == ph->data.nb_of_philos - 1)
			ph->philo[index].right_fork = &ph->philo[0].left_fork;
		else
			ph->philo[index].right_fork = &ph->philo[index + 1].left_fork;
		index ++;
	}
	return (1);
}
