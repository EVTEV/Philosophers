#include "../../inc/philo.h"

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	*start_meal(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->nbr_meal < 5)
	{
		printf("Philosopher %d is thinking...\n", philo->id);
		if (philo->id % 2 == 1)
		{
			pthread_mutex_lock(philo->right_fork);
			printf("Philosopher %d took right fork\n", philo->id);
			pthread_mutex_lock(philo->left_fork);
			printf("Philosopher %d took left fork and is eating\n", philo->id);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			printf("Philosopher %d took left fork\n", philo->id);
			pthread_mutex_lock(philo->right_fork);
			printf("Philosopher %d took right fork and is eating\n", philo->id);
		}
		philo->time_meal = get_time();
		usleep(1000000);
		philo->nbr_meal++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("Philosopher %d released forks and is sleeping\n", philo->id);
		usleep(1000000);
	}
	return (NULL);
}

void	*dead_philo(void *args)
{
	t_table		*table;
	long long	time;
	int			i;

	table = (t_table *)args;
	while (1)
	{
		i = 0;
		time = get_time();
		while (i < table->num_philo)
		{
			if ((time - table->philo[i].time_meal) > 5000)
			{
				printf("Philosopher %d has died !\n", table->philo[i].id);
				exit(1);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
