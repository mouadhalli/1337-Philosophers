#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	//• The program should take the following arguments: number_of_philosophers time_to_die 
	//time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
    //this struct contain informations about the simulation
    int	philos;
	int timeto_die;
	int timeto_eat;
	int timeto_sleep;
	int meals;
	long long init_time;
	pthread_mutex_t write;

} t_data;

typedef struct s_philo
{
    /*

    */
    //this struct will contain data for each philo
} t_philo;

//----------------- UTILS FUNCTIONS ---------------//
long long get_timeNow();

#endif