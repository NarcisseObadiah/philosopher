/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:30:07 by mobadiah         #+#    #+#             */
/*   Updated: 2023/10/06 14:29:49 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	is_digit(char **argv, int k, int j)
{
	while (argv[j])
	{
		while (argv[j][k])
		{
			if (argv[j][k] < '0' || argv[j][k] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			k++;
		}
		k = 0;
		j++;
	}
	return (1);
}

int	ft_parsing(int argc, char **argv, t_philo *ph)
{
	if ((argc == 5 || argc == 6) && is_digit(argv, 0, 1))
	{
		ph->data.nb_of_philos = ft_atoi(argv[1]);
		ph->data.time_to_die = ft_atoi(argv[2]);
		ph->data.time_to_eat = ft_atoi(argv[3]);
		ph->data.time_to_sleep = ft_atoi(argv[4]);
		ph->data.times_must_eat = -1;
		if (argc == 6)
			ph->data.times_must_eat = ft_atoi(argv[5]);
		if (ph->data.nb_of_philos <= 0 || ph->data.time_to_die <= 0)
			return (0);
		if (ph->data.time_to_eat <= 0 || ph->data.time_to_sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}
