/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <mhalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:45:19 by mhalli            #+#    #+#             */
/*   Updated: 2022/02/22 11:22:45 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_write(t_data *data, char *msg, int philo_id, int lock)
{
	pthread_mutex_lock(&data->write);
	printf("%lld ", timenow() - data->init_time);
	printf("philo %d %s\n", philo_id, msg);
	if (!lock)
		pthread_mutex_unlock(&data->write);
}

long long	timenow(void)
{
	struct timeval	timevalue;

	gettimeofday(&timevalue, NULL);
	return ((timevalue.tv_sec * 1000) + (timevalue.tv_usec / 1000));
}

void	ft_usleep(long long sleep_duration)
{
	long long	start;

	start = timenow();
	usleep((sleep_duration - 5) * 1000);
	while ((timenow() - sleep_duration) < start)
		;
}

int	exit_error(char *msg, int status)
{
	printf("Error:\n    %s\n", msg);
	return (status);
}

int	free_philos(t_data *data, t_philo *philos)
{
	t_philo	*head;
	t_philo	*tmp;
	t_philo	*iterator;

	head = philos;
	iterator = philos->next;
	while (iterator != head)
	{
		tmp = iterator->next;
		pthread_mutex_destroy(&iterator->fork);
		free(iterator);
		iterator = tmp;
	}
	pthread_mutex_destroy(&head->fork);
	free(head);
	philos = NULL;
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->is_eating);
	free(data);
	data = NULL;
	return (0);
}
