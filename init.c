/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <mhalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:39:17 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/21 21:40:52 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philo(int philo_nbr, t_data *data, t_philo *philo)
{
	philo->id = philo_nbr;
	philo->meal_nbr = 0;
	philo->is_eating = 0;
	philo->lst_meal = data->init_time;
	philo->data = data;
	pthread_mutex_init(&philo->fork, NULL);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*head;
	t_philo	*tmp;
	int		philo_nbr;

	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	philo_nbr = 1;
	tmp = head;
	while (philo_nbr <= data->philos)
	{
		create_philo(philo_nbr, data, tmp);
		if (philo_nbr == data->philos)
			tmp->next = head;
		else
		{
			tmp->next = malloc(sizeof(t_philo));
			if (tmp->next == NULL)
				return (NULL);
		}
		tmp = tmp->next;
		philo_nbr++;
	}
	return (head);
}

int	filter_data(char **data)
{
	int	i;
	int	j;

	i = 0;
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
		{
			if (data[i][0] == '-' || !ft_isdigit(data[i][j])
					|| ft_strlen(data[i]) > 10
				|| (j == 9 && strcmp(data[i], "2147483647") > 0))
				return (0);
		}
	}
	return (1);
}

t_data	*init_simulation(char **data, int argc)
{
	t_data	*simulation_data;

	simulation_data = malloc(sizeof(t_data));
	if (!simulation_data || argc < 5 || argc > 6 || !filter_data(data))
		return (NULL);
	simulation_data->philos = ft_atoi(data[1]);
	simulation_data->die_time = ft_atoi(data[2]);
	simulation_data->timeto_eat = ft_atoi(data[3]);
	simulation_data->timeto_sleep = ft_atoi(data[4]);
	simulation_data->init_time = timenow();
	simulation_data->meals = -1;
	if (argc > 5)
		simulation_data->meals = ft_atoi(data[5]);
	pthread_mutex_init(&simulation_data->write, NULL);
	return (simulation_data);
}
