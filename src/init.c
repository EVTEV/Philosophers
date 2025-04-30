#include "../inc/philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meal_stop = false;
	if (ac == 6)
		data->num_meal =  ft_atoi(av[5]);
	else
		data->num_meal = -1;
	if (data->num_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->num_meal <= 0))
	{
		printf("Error:\nInvalid arguments\n");
		return(1);
	}
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
	{
		printf("Error:\nMemory allocation failed\n");
		return (1);
	}
	data->fork = malloc(sizeof(t_fork) * data->num_philo);
    if (!data->fork)
    {
		printf("Error:\nMemory allocation failed for forks\n");
		free(data->philo);
		return (1);
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Error:\nFailed to initialize mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		printf("Error:\nFailed to initialize mutex\n");
		return (1);
	}
	return (0);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->fork[i].id = i + 1;
		if (pthread_mutex_init(&data->fork[i].mutex, NULL) != 0)
		{
			printf("Error:\nFailed to initialize fork mutex\n");
			while (--i >= 0)
				pthread_mutex_destroy(&data->fork[i].mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].state = THINKING;
		data->philo[i].meal_eat = 0;
		data->philo[i].time_meal = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1) % data->num_philo];
		i++;
	}
	return (0);
}
