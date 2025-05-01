#include "../inc/philo.h"

/* Check if all philosophers have eaten enough meals */
static int	check_if_finish(t_data *data)
{
	int	i;
	int	finish;

	if (data->num_meals == -1)
		return (0);
	finish = 0;
	i = 0;
	pthread_mutex_lock(&data->dead_mutex);
	while (i < data->num_philo)
	{
		if (data->philo[i].meal_eat >= data->num_meal)
			finish++;
		i++;
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (finish == data->num_philos);
}

/* Check if any philosopher has died */
static int	check_if_death(t_data *data)
{
	int			i;
	long long	current;
	long long	last_meal;

	current = get_time();
	i = 0;
	pthread_mutex_lock(&data->dead_mutex);
	while (i < data->num_philo)
	{
		if (data->philo[i].time_meal == 0)
		{
			i++;
			continue ;
		}
		last_meal = current - data->philo[i].time_meal;
		if (last_meal > data->time_to_die)
		{
			data->stop_all = true;
			pthread_mutex_unlock(&data->dead_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", 
				current - data->start, data->philo[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

/* Main routine for the monitoring thread */
void	*monitor_routine(void *arg)
{
	t_data	*data;
	bool	stop_routine;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		if (check_if_death(data))
			break ;
		if (check_if_finish(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->stop_all = true;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_lock(&data->dead_mutex);
		stop_routine = data->stop;
		pthread_mutex_unlock(&data->dead_mutex);
		if (stop_routine)
			break ;
		usleep(1000); 
	}
	return (NULL);
}
