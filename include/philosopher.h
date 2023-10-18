/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:00:13 by mobadiah          #+#    #+#             */
/*   Updated: 2023/10/18 15:49:58 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# define MAX_LONG 2147483647

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;			
	long int		starting_time;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_time_eat;
	pthread_mutex_t	mutex_end;
	int				num_phil_finished;
	int				status;
}					t_data;

// int				num_phil_finished; number of philosopher that  finish eating
// int				status;  0 if none philosopher ate, 1 if a philo is dead,
// 							2 if all philo ate times_must_eat 

typedef struct s_ph
{
	int				id;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_data			*pdata;
	long int		last_eat_time;
	unsigned int	num_eat;
	int				end;
}					t_ph;

// t_data	*pdata; 		pointer to struct with all arguments
// unsigned int	num_eat; 	number of diner, each time a philo eat, num_eat++
// pthread_t				thread_death_id; id of the thread monitoring death.

typedef struct s_philo
{
	t_ph	*philo;
	t_data	data;
}		t_philo;

int			init_data(t_philo	*ph);
long int	time_now(void);
void		ft_usleep(long int time_in_ms);
int			ft_check_death(t_ph *philo, int i);
int			ft_parsing(int argc, char **argv, t_philo *ph);
void		write_status(char *str, t_ph *philo);
void		ft_routine(t_ph	*philo);
int			ft_strlen(const char *s);
int			ft_error(char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* threads functions*/

void		mark_philosopher_as_finished(t_ph *philo);
int			ft_threading(t_philo *ph);

#endif
