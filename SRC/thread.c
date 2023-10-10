/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:00:31 by mobadiah          #+#    #+#             */
/*   Updated: 2023/10/10 16:34:39 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*Function to check if a philosopher is dead, if yes it writes it
 and change the status. This is done by the uses of mutex to allow the acces
 to philo(thread) at time.
*/

void	*ft_is_dead(void *data)
{
	t_ph		*philo;
	int			is_dead;
	long		time_since_eat;

	philo = (t_ph *)data;
	is_dead = ft_check_death(philo, 0);
	time_since_eat = time_now() - philo->last_eat_time;

	pthread_mutex_lock(&philo->pdata->mutex_time_eat);
	// pthread_mutex_lock(&philo->pdata->mutex_end);
	if (!is_dead && time_since_eat >= (long)(philo->pdata->time_to_die))
	{
		pthread_mutex_unlock(&philo->pdata->mutex_time_eat);
		// pthread_mutex_unlock(&philo->pdata->mutex_end);
		pthread_mutex_lock(&philo->pdata->mutex_write);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->pdata->mutex_write);
		ft_check_death(philo, 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->pdata->mutex_time_eat);
		// pthread_mutex_unlock(&philo->pdata->mutex_end);
	}
	return (NULL);
}
// /*
// This thread fucntion make sure that not all 
// the philos start eating together by usleeping those
// of them whose has an odd id's
// so that there eating time will be delay.
// Also runs an aside thread to currently check for a dead philo
// by using thread_death_id inside a pthread_create which runs a 
// ft_is_dead fucntion.Then start the routine fucntion.
// During that process, after a  philo has eaten
// the number of time his is supposed to eat, the counter 
// of the num_phil_finished++ increase.
// Finaly, if the number of philo that has finished to eat is 
// equal to the total number of philosopher, then the status change
//  ft_check_death(philo, 2), 2->which means all the philo have eaten;
//  a mutex is used on end variable to make sure 
//  that only one thread has access time
 
// */

// void	*ft_thread(void *data)
// {
// 	t_ph	*philo;

// 	philo = (t_ph *)(data);
// 	if ((philo->id % 2) == 0)
// 		ft_usleep(philo->pdata->time_to_eat / 10);
// 	while (!ft_check_death(philo, 0))
// 	{
// 		pthread_create(&philo->thread_death_id, NULL, ft_is_dead, data);
// 		ft_routine(philo);
// 		pthread_detach(philo->thread_death_id);
// 		if ((int)++philo->num_eat == philo->pdata->times_must_eat)
// 		{
// 			pthread_mutex_lock(&philo->pdata->mutex_end);
// 			philo->end = 1;
// 			philo->pdata->num_phil_finished++;
// 			if (philo->pdata->num_phil_finished == philo->pdata->nb_of_philos)
// 			{
// 				pthread_mutex_unlock(&philo->pdata->mutex_end);
// 				ft_check_death(philo, 2);
// 			}
// 			pthread_mutex_unlock(&philo->pdata->mutex_dead);
// 		}
// 	}
// 	return (NULL);
// }

/*
	// Lock the end mutex to safely update shared variables
	// Check if all philosophers have finished, and if so, trigger the end condition
	// Unlock the death mutex
*/

void	mark_philosopher_as_finished(t_ph *philo)
{
	pthread_mutex_lock(&philo->pdata->mutex_end);
	philo->end = 1;
	philo->pdata->num_phil_finished++;
	if (philo->pdata->num_phil_finished == philo->pdata->nb_of_philos)
	{
		pthread_mutex_unlock(&philo->pdata->mutex_end);
		ft_check_death(philo, 2);
	}
	pthread_mutex_unlock(&philo->pdata->mutex_dead);
}

/*
	// Check if philosopher ID is even and sleep if true
	// Continuously check if the philosopher is alive
	// Start a thread to check for philosopher's death
	// Perform the routine for the philosopher
	// Detach the death-checking thread
	// Check if the philosopher has reached the required number of meals
	// Mark the philosopher as finished and handle the end condition
	
*/

void	*ft_thread(void *data)
{
	t_ph	*philo;

	philo = (t_ph *)(data);
	if (philo->id % 2 == 0)
		ft_usleep(philo->pdata->time_to_eat / 10);
	while (!ft_check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, ft_is_dead, data);
		ft_routine(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->num_eat == philo->pdata->times_must_eat)
		{
			mark_philosopher_as_finished(philo);
		}
	}
	return (NULL);
}
/*
	// Loop through the philosophers and create a thread for each
	// Create a thread for the philosopher's routine
	// Return an error code on failure
*/

int	ft_threading(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->data.nb_of_philos)
	{
		ph->philo[i].pdata = &ph->data;
		if (pthread_create(&ph->philo[i].thread_id, NULL, ft_thread, \
			&ph->philo[i]) != 0)
			(ft_error("Pthread did not return 0"));
		i++;
	}
	return (1);
}


