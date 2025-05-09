/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:11 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 11:48:11 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static int	handle_error(t_data *data)
{
	pthread_mutex_lock(&data->mutex_stop_all);
	data->stop_all = true;
	pthread_mutex_unlock(&data->mutex_stop_all);
	cleanup(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat"
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutex(&data) != 0)
		return (handle_error(&data));
	if (init_fork(&data) != 0)
		return (handle_error(&data));
	if (init_philo(&data) != 0)
		return (handle_error(&data));
	if (start_process(&data) != 0)
		return (handle_error(&data));
	cleanup(&data);
	return (0);
}
