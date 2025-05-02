/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:11:13 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:11:13 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* =========================== UTILS FOR ROUTINE ============================ */

#include "../inc/philo.h"

/* Check if routine should stop */
bool	check_stop_condition(t_philo *philo)
{
	bool	should_stop;
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->dead_mutex);
	should_stop = data->stop_all;
	pthread_mutex_unlock(&data->dead_mutex);
	return (should_stop);
}

/* Function to take both forks */
void	take_forks(t_philo *philo)
{
	if (philo->left_fork->id < philo->right_fork->id)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_status(philo, "has taken a fork");
	}
}

/* Function to release both forks */
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

/* Check if philosopher has eaten enough meals */
bool	has_eaten_enough(t_philo *philo)
{
	t_data	*data;
	bool	enough;

	data = philo->data;
	pthread_mutex_lock(&data->dead_mutex);
	enough = (data->num_meal != -1 && philo->meal_eat >= data->num_meal);
	pthread_mutex_unlock(&data->dead_mutex);
	return (enough);
}
