/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:10:05 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:10:05 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ============================= THREAD_PROCESS ============================= */

#include "../inc/philo.h"

/* Function for philosopher to eat */
void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	pthread_mutex_lock(&data->mutex_stop_all);
	philo->state = EATING;
	philo->time_meal = get_time();
	pthread_mutex_unlock(&data->mutex_stop_all);
	print_status(philo, "is eating");
	precise_sleep(data->time_to_eat);
	pthread_mutex_lock(&data->mutex_stop_all);
	philo->meal_eat++;
	pthread_mutex_unlock(&data->mutex_stop_all);
	release_forks(philo);
}

/* Function for philosopher to sleep */
void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mutex_stop_all);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&data->mutex_stop_all);
	print_status(philo, "is sleeping");
	precise_sleep(data->time_to_sleep);
}

/* Function for philosopher to think */
void	philo_think(t_philo *philo)
{
	long long	think_time;

	pthread_mutex_lock(&philo->data->mutex_stop_all);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->data->mutex_stop_all);
	print_status(philo, "is thinking");
	if (philo->data->num_philo % 2 == 0)
	{
		think_time = (philo->data->time_to_die - (philo->data->time_to_eat
					+ philo->data->time_to_sleep)) / 2;
		if (think_time > 200)
			think_time = 200;
		else if (think_time < 0)
			think_time = 0;
		precise_sleep(think_time);
	}
}

/* Main routine for each philosopher thread */
void	*thread_process(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(data->time_to_eat * 500);
	if (data->num_philo == 1)
	{
		print_status(philo, "has taken a fork");
		precise_sleep(data->time_to_die);
		return (NULL);
	}
	while (!check_stop_condition(philo) && !has_eaten_enough(philo))
	{
		philo_eat(philo);
		if (check_stop_condition(philo) || has_eaten_enough(philo))
			break ;
		philo_sleep(philo);
		if (check_stop_condition(philo) || has_eaten_enough(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
