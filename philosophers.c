#include "philosophers.h"

int filter_data(char **data)
{
    int     i;
	int		j;

    i = 0;
    while (data[++i])
    {
		j = -1;
		while (data[i][++j])
		{
			if (data[i][0] == '-' || !ft_isdigit(data[i][j]) || ft_strlen(data[i]) > 10
				|| (j == 9 && strcmp(data[i], "2147483647") > 0))
				return (0);
		}
    }
    return (1);
}

t_data	*init_simulation(char **data, int argc)
{
	t_data *simulation_data;

	simulation_data = malloc(sizeof(t_data));
	if (!simulation_data || argc < 5 || argc > 6 || !filter_data(data))
		return (NULL);
	simulation_data->philos = ft_atoi(data[1]);
	simulation_data->timeto_die = ft_atoi(data[2]);
	simulation_data->timeto_eat = ft_atoi(data[3]);
	simulation_data->timeto_sleep = ft_atoi(data[4]);
	simulation_data->init_time = get_timenow();
	simulation_data->meals = -1;
	if (argc > 5)
		simulation_data->meals = ft_atoi(data[5]);
	pthread_mutex_init(&simulation_data->write, NULL);
	return (simulation_data);
}

void	create_philo(int philo_nbr, t_data *data, t_philo *philo)
{
	philo->id = philo_nbr;
	philo->meal_nbr = 0;
	philo->is_eating = 0;
	philo->last_meal = data->init_time;
	philo->data = data;
	pthread_mutex_init(&philo->fork, NULL);
}

t_philo	*init_philos(t_data *data)
{
	t_philo *head;
	t_philo *tmp;
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

void	philo_write(t_data *data, char *msg, int philo_id)
{
	pthread_mutex_lock(&data->write);
	printf("%lld ", get_timenow() - data->init_time);
	printf("philo %d %s\n", philo_id, msg);
	pthread_mutex_unlock(&data->write);
}

void	*daily_routine(void	*philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	while (philo->meal_nbr <= philo->data->meals)
	{
		pthread_mutex_lock(&philo->fork);
		philo_write(philo->data, "took a fork", philo->id);
		pthread_mutex_lock(&philo->next->fork);
		philo_write(philo->data, "is eating", philo->id);
		philo->is_eating = 1;
		philo->last_meal = get_timenow();
		philo->is_eating = 0;
		philo->meal_nbr += 1;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo_write(philo->data, "is sleeping", philo->id);
		ft_usleep(philo->data->timeto_sleep);
		philo_write(philo->data, "is thinking", philo->id);
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
		pthread_create(&philos->philo, NULL, &daily_routine, philos);
		usleep(50);
		philos = philos->next;
		philo_nbr++;
	}
}

int main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	data = init_simulation(argv, argc);
    if (!data)
		return (exit_error("invalid arguments", 1));
	if (!data->philos || !data->meals)
		return (0);
	philos = init_philos(data);
	if (!philos)
		return (exit_error("Malloc has failed", 1));
	start_simulation(philos);
	while (1)
	{
		if (philos->data->philos == 0)
			break ;
		if (philos->is_eating == 0)
		{
			if (philos->id && (get_timenow() - philos->last_meal > philos->data->timeto_die))
			{
				philo_write(philos->data, "died", philos->id);
				break ;
			}
			philos = philos->next;
		}
	}
    return (0);
}
