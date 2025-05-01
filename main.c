#include "inc/philo.h"

static int	r_one(t_data *data)
{
	cleanup(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		r_one(&data);
	if (init_forks(&data) != 0)
		r_one(&data);
	if (init_philo(&data) != 0)
		r_one(&data);
	if (start_routine(&data) != 0)
		r_one(&data);
	cleanup(&data);
	return (0);
}
