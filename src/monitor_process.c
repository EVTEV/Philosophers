/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:04:14 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:04:14 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ============================ MONITOR_PROCESS ============================= */

#include "../inc/philo.h"

/* Check if a specific philosopher has died due to starvation */
static int	is_philo_dead(t_data *data, int i, long long current)
{
	long long	last_meal;

	if (data->philo[i].time_meal == 0)
		return (0);
	last_meal = current - data->philo[i].time_meal;
	if (last_meal > data->time_to_die)
	{
		data->stop_all = true;
		pthread_mutex_unlock(&data->mutex_stop_all);
		pthread_mutex_lock(&data->mutex_state);
		printf("%lld %d died\n",
			current - data->start, data->philo[i].id);
		pthread_mutex_unlock(&data->mutex_state);
		return (1);
	}
	return (0);
}

/* Check if any philosopher has died due to starvation */
static int	check_if_death(t_data *data)
{
	int			i;
	long long	current;

	current = get_time();
	i = 0;
	pthread_mutex_lock(&data->mutex_stop_all);
	while (i < data->num_philo)
	{
		if (is_philo_dead(data, i, current))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&data->mutex_stop_all);
	return (0);
}

/* Check if all philosophers have eaten enough meals */
static int	check_if_finish(t_data *data)
{
	int	i;
	int	finish;

	if (data->num_meal == -1)
		return (0);
	finish = 0;
	i = 0;
	pthread_mutex_lock(&data->mutex_stop_all);
	while (i < data->num_philo)
	{
		if (data->philo[i].meal_eat >= data->num_meal)
			finish++;
		i++;
	}
	pthread_mutex_unlock(&data->mutex_stop_all);
	return (finish == data->num_philo);
}

/* Main routine for the monitoring thread to check death and meal completion */
void	*monitor_process(void *arg)
{
	t_data	*data;
	bool	stop_process;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		if (check_if_death(data))
			break ;
		if (check_if_finish(data))
		{
			pthread_mutex_lock(&data->mutex_stop_all);
			data->stop_all = true;
			pthread_mutex_unlock(&data->mutex_stop_all);
			break ;
		}
		pthread_mutex_lock(&data->mutex_stop_all);
		stop_process = data->stop_all;
		pthread_mutex_unlock(&data->mutex_stop_all);
		if (stop_process)
			break ;
		usleep(1000);
	}
	return (NULL);
}
