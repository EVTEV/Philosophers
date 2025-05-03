/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:12:02 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:12:02 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ================================= TIMESTAMP ================================== */

#include "../inc/philo.h"

/* Get current time in milliseconds */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Calculate time difference between two timestamps */
long long	time_diff(long long past, long long present)
{
	return (present - past);
}

/* Sleep for a precise amount of time in milliseconds */
void	precise_sleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
}

/* Print philosopher status message with timestamp */
void	print_status(t_philo *philo, char *status)
{
	long long	current_time;
	t_data		*data;
	bool		should_stop;

	data = philo->data;
	pthread_mutex_lock(&data->mutex_stop_all);
	should_stop = data->stop_all;
	pthread_mutex_unlock(&data->mutex_stop_all);
	if (should_stop)
		return ;
	current_time = get_time() - data->start;
	pthread_mutex_lock(&data->mutex_state);
	printf("%lld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&data->mutex_state);
}
