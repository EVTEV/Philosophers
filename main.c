#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_table		*table;
	pthread_t	monitor;
	int			num_philo;
	int			i;

	if (ac != 2)
	{
		printf("Error\n %s invalid number of argument\n", av[0]);
		return (1);
	}
	num_philo = atoi(av[1]);
	table = init_table(num_philo);
	if (!table)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, start_meal, &table->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, dead_philo, table);
	pthread_detach(monitor);
	i = 0;
	while (i < num_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philo);
	free(table);
	return (0);
}
