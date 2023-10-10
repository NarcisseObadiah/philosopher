/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:31 by narcisse          #+#    #+#             */
/*   Updated: 2023/10/10 19:10:29 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

// Function to check if it's safe to stop
// Save the status
// Return the saved status

int	last_death_checking(t_philo *ph)
{
	pthread_mutex_lock(&ph->data.mutex_dead);
	if (ph->data.status)
	{
		pthread_mutex_unlock(&ph->data.mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->data.mutex_dead);
	return (0);
}

void	ft_stop(t_philo *ph)
{
	int	i;

	i = 0;
	while (!last_death_checking(ph))
		ft_usleep(1);
	while (i++ < ph->data.nb_of_philos)
		pthread_join(ph->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&ph->data.mutex_write);
	i = 0;
	while (i++ < ph->data.nb_of_philos)
		pthread_mutex_destroy(&ph->philo[i].left_fork);
	if (ph->data.status == 2)
		printf("Each philosopher ate %d time(s)\n", ph->data.times_must_eat);
	free(ph->philo);
}


int	main(int argc, char **argv)
{
	t_philo		ph;

	if (!(ft_parsing(argc, argv, &ph)))
		return (ft_error("Invalid Arguments"));
	ph.philo = malloc(sizeof(t_philo) * ph.data.nb_of_philos);
	if (!ph.philo)
		return (ft_error("Malloc returned NULL"));
	if (!init_data(&ph) || !ft_threading(&ph))
	{
		free(ph.philo);
		return (0);
	}
	ft_stop(&ph);
}

