/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 06:32:07 by mobadiah          #+#    #+#             */
/*   Updated: 2023/10/07 15:35:54 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_error(char *str)
{
	write(1, &str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

long int	time_now(void)
{
	long int		time;
	struct timeval	cur_time;

	time = 0;
	if (gettimeofday(&cur_time, NULL) == -1)
		ft_error("Get time error!!!");
	time = ((cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000));
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	starting_time;

	starting_time = 0;
	starting_time = time_now();
	while ((time_now() - starting_time) < time_in_ms)
	{
		usleep(time_in_ms / 10);
	}
}

int	ft_check_death(t_ph *philo, int i)
{
	int	is_stopped;

	pthread_mutex_lock(&philo->pdata->mutex_dead);
	if (i > 0)
		philo->pdata->status = i;
	is_stopped = philo->pdata->status;
	pthread_mutex_unlock(&philo->pdata->mutex_dead);
	return (is_stopped);
}
