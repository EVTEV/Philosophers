/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:49:00 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 11:49:00 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ================================ CLEANUP ================================= */

#include "../inc/philo.h"

/* Function for destroy mutexes and frees allocated memory */
void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->fork[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
}
