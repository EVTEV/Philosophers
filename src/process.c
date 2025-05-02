/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:08:42 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:08:42 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* =============================== PROCESS ================================== */

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
			pthread_mutex_lock(&data->dead_mutex);
			data->stop_all = true;
			pthread_mutex_unlock(&data->dead_mutex);
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (msg_error("Failed to create philosopher thread"));
		}
		i++;
	}
	return (0);
}

/* Function to create monitoring thread for death and completion */
int	create_monitor(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL,
			monitor_routine, data) != 0)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->stop_all = true;
		pthread_mutex_unlock(&data->dead_mutex);
		join_philo(data);
		return (msg_error("Failed to create monitor thread"));
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
			return (msg_error("Failed to join philosopher thread"));
		}
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		return (msg_error("Failed to join monitor thread"));
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
