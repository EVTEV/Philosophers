/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:33 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:01:33 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ================================= INIT PHILO ============================== */

#include "../inc/philo.h"

/* Initialize philosopher structures and assign forks */
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