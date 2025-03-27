#include "../../inc/philo.h"

t_table	*init_table(int num_philo)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->num_philo = num_philo;
	table->forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	table->philo = malloc(sizeof(t_philo) * num_philo);
	if (!table->forks || !table->philo)
		return (NULL);
	i = 0;
    while (i < num_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		table->philo[i].id = i;
		table->philo[i].nbr_meal = 0;
		table->philo[i].time_meal = get_time();
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % num_philo];
		i++;
	}
	return (table);
}


