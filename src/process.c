#include "../inc/philo.h"

/* Function to create all philosopher threads */
int	create_philo(t_data *data)
{
	int	i;

	data->start = get_time();
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].time_meal = data->start;
		if (pthread_create(&data->philo[i].thread, NULL,
			philo_routine, &data->philo[i]) != 0)
		{
			printf("Error:\nFailed to create philosopher thread\n");
			pthread_mutex_lock(&data->dead_mutex);
			data->stop_all = true;
			pthread_mutex_unlock(&data->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Function to create monitoring thread */
int	create_monitor(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL,
		monitor_routine, data) != 0)
	{
		printf("Error:\n Failed to create monitor thread\n");
		pthread_mutex_lock(&data->dead_mutex);
		data->stop_all = true;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

/* Function to wait for all philosopher threads to finish */
int	join_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Error:\n Failed to join philosopher thread\n");
			return (1);
		}
		i++;
	}	
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		printf("Error:\n Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}

/* Creates all threads and waits for them to finish */
int	start_routine(t_data *data)
{
	if (create_philo(data) != 0)
		return (1);
	if (create_monitor(data) != 0)
		return (1);
	if (join_philo(data) != 0)
		return (1);
	return (0);
}
