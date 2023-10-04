#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct s_data
{
    int nb_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_must_eat;
    long int starting_time;
    pthread_mutex_t mutex_write;
    pthread_mutex_t mutex_dead;
    pthread_mutex_t mutex_time_eat;
    pthread_mutex_t mutex_end;
    int num_phil_finished; //number of philosopher that  finish eating
    int stop;     //0 if none philosopher ate, 1 if a philo is dead, 2 if all philo ate times_must_eat 
}   t_data;


typedef struct s_ph
{
    int id;
    pthread_t   thread_id;
    pthread_t   thread_death_id; //id of the thread monitoring death.
    pthread_mutex_t   *right_fork;
    pthread_mutex_t   left_fork;
    long int last_eat_time;
    int    num_eat; //number of eating, each time the philo eat, num_eat++
    int     end;   // 1 when a philosopher ate times_must_eat, if not 0.
}           t_ph;


typedef struct s_philo
{
    t_ph *philo;
    t_data  data;
}           t_philo;

int     init_data(t_philo  *ph);
long int time_now(void);

#endif
