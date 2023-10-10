/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:34:43 by mobadiah          #+#    #+#             */
/*   Updated: 2023/10/10 19:17:37 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	write_status(char *str, t_ph *philo)
{
	long int	time;

	time = -1;
	time = time_now() - philo->pdata->starting_time;
	if (time >= 0 && time <= MAX_LONG && !ft_check_death(philo, 0))
		printf("%ld Philo %d %s", time, philo->id, str);
}


void	ft_sleep(t_ph *philo)
{
	pthread_mutex_lock(&philo->pdata->mutex_write);
	write_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->pdata->mutex_write);
}

void	ft_think(t_ph *philo)
{
	pthread_mutex_lock(&philo->pdata->mutex_write);
	write_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->pdata->mutex_write);
}

void	ft_routine(t_ph *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->pdata->mutex_write);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->pdata->mutex_write);
	if (!philo->right_fork)
	{
		ft_usleep(philo->pdata->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->pdata->mutex_write);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->pdata->mutex_write);
	pthread_mutex_lock(&philo->pdata->mutex_write);
	write_status("is eating\n", philo);
	pthread_mutex_lock(&philo->pdata->mutex_time_eat);
	philo->last_eat_time = time_now();
	pthread_mutex_unlock(&philo->pdata->mutex_time_eat);
	pthread_mutex_unlock(&philo->pdata->mutex_write);
	ft_usleep(philo->pdata->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	ft_sleep(philo);
	ft_think(philo);
}
