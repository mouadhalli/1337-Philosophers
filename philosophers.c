/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <mhalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:23:44 by mhalli            #+#    #+#             */
/*   Updated: 2022/02/22 10:37:24 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*deadly_routine(void	*philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	while (philo->meal_nbr != philo->data->meals)
	{
		pthread_mutex_lock(&philo->fork);
		philo_write(philo->data, "took a fork", philo->id, 0);
		pthread_mutex_lock(&philo->next->fork);
		philo_write(philo->data, "is eating", philo->id, 0);
		// philo->is_eating = 1;
		pthread_mutex_lock(&philo->data->is_eating);
		philo->lst_meal = timenow();
		pthread_mutex_unlock(&philo->data->is_eating);
		// philo->is_eating = 0;
		ft_usleep(philo->data->timeto_eat);
		philo->meal_nbr += 1;
		pthread_mutex_unlock(&philo->data->is_eating);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo_write(philo->data, "is sleeping", philo->id, 0);
		ft_usleep(philo->data->timeto_sleep);
		philo_write(philo->data, "is thinking", philo->id, 0);
	}
	philo->id = 0;
	philo->data->philos -= 1;
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int		philo_nbr;

	philo_nbr = 1;
	while (philo_nbr <= philos->data->philos)
	{
		pthread_create(&philos->philo, NULL, &deadly_routine, philos);
		usleep(55);
		philos = philos->next;
		philo_nbr++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*phil;

	data = init_simulation(argv, argc);
	if (!data)
		return (exit_error("invalid arguments", 1));
	if (!data->philos || !data->meals)
		return (0);
	phil = init_philos(data);
	if (!phil)
		return (exit_error("Malloc has failed", 1));
	start_simulation(phil);
	while (phil->data->philos != 0)
	{
		pthread_mutex_lock(&phil->data->is_eating);
		if (phil->id && (timenow() - phil->lst_meal > phil->data->die_time))
		{
			philo_write(phil->data, "died", phil->id, 1);
			return (free_philos(data, phil));
		}
		pthread_mutex_unlock(&phil->data->is_eating);
		phil = phil->next;
	}
	return (free_philos(data, phil));
}
