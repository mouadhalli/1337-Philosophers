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

int	init_simulation(char **data, int argc)
{
	t_data *simulation_data;

	simulation_data = malloc(sizeof(t_data));
	if (!data || !filter_data(data))
		return (0);
	simulation_data->philos = ft_atoi(data[1]);
	simulation_data->timeto_die = ft_atoi(data[2]);
	simulation_data->timeto_eat = ft_atoi(data[3]);
	simulation_data->timeto_sleep = ft_atoi(data[4]);
	simulation_data->init_time = get_timeNow();
	if (argc > 5)
		simulation_data->meals = ft_atoi(data[5]);
	pthread_mutex_init(&simulation_data->write, NULL);
	return (1);
}

int main(int argc, char **argv)
{

    if (argc < 5 || argc > 6 || !init_simulation(argv, argc))
    {
        printf("Error:\n    invalid arguments\n");
        return (1);
    }
    return (0);
}