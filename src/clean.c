#include "../inc/philo.h"

//================================ CLEANUP =================================//
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


