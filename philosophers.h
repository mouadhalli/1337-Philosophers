/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <mhalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:41:42 by mhalli            #+#    #+#             */
/*   Updated: 2022/02/22 10:25:25 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philos;
	int				die_time;
	int				timeto_eat;
	int				timeto_sleep;
	int				meals;
	long long		init_time;
	pthread_mutex_t	write;
	pthread_mutex_t	is_eating;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meal_nbr;
	long long		lst_meal;
	pthread_mutex_t	fork;
	pthread_t		philo;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

long long	timenow(void);

int			exit_error(char *msg, int status);
void		ft_usleep(long long sleep_time);
int			free_philos(t_data *data, t_philo *philos);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		philo_write(t_data *data, char *msg, int philo_id, int lock);
t_data		*init_simulation(char **data, int argc);
t_philo		*init_philos(t_data *data);

#endif
