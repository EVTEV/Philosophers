#include "../inc/philo.h"

// Simple function to print philosophers info for testing
void print_philo_info(t_data *data)
{
	int i;
	
	printf("\n========= PHILOSOPHERS INFO =========\n");
	for (i = 0; i < data->num_philo; i++)
	{
		printf("Philosopher %d:\n", data->philo[i].id);
		printf("  - State: %d\n", data->philo[i].state);
		printf("  - Left fork ID: %d\n", data->philo[i].left_fork->id);
		printf("  - Right fork ID: %d\n", data->philo[i].right_fork->id);
		printf("  - Meals eaten: %d\n", data->philo[i].meal_eat);
		printf("\n");
	}
	printf("====================================\n\n");
}

// Simple function to print data structure info for testing
void print_data_info(t_data *data)
{
	printf("\n========= SIMULATION PARAMETERS =========\n");
	printf("Number of philosophers: %d\n", data->num_philo);
	printf("Time to die: %d ms\n", data->time_to_die);
	printf("Time to eat: %d ms\n", data->time_to_eat);
	printf("Time to sleep: %d ms\n", data->time_to_sleep);
	printf("Number of meals: %d\n", data->num_meal);
	printf("=========================================\n\n");
}

int main(int argc, char **argv)
{
	t_data data;
	int i;
	
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	
	// Test init_data
	printf("Testing init_data...\n");
	if (init_data(&data, argc, argv) != 0)
	{
		printf("Error: init_data failed\n");
		return (1);
	}
	printf("init_data succeeded!\n");
	print_data_info(&data);
	
	// Test init_mutexes
	printf("Testing init_mutexes...\n");
	if (init_mutex(&data) != 0)
	{
		printf("Error: init_mutexes failed\n");
		clean_resource(&data);
		return (1);
	}
	printf("init_mutexes succeeded!\n");
	
	// Test init_forks
	printf("Testing init_forks...\n");
	if (init_fork(&data) != 0)
	{
		printf("Error: init_forks failed\n");
		clean_resource(&data);
		return (1);
	}
	printf("init_forks succeeded!\n");
	
	// Verify forks were initialized properly
	printf("\n========= FORKS INFO =========\n");
	for (i = 0; i < data.num_philo; i++)
	{
		printf("Fork %d initialized\n", data.fork[i].id);
	}
	printf("==============================\n\n");
	
	// Test init_philosophers
	printf("Testing init_philosophers...\n");
	if (init_philo(&data) != 0)
	{
		printf("Error: init_philosophers failed\n");
		clean_resource(&data);
		return (1);
	}
	printf("init_philosophers succeeded!\n");
	// Print philosopher info to verify
	print_philo_info(&data);
	// Test cleanup
	printf("Testing cleanup_resources...\n");
	clean_resource(&data);
	printf("cleanup_resources completed!\n");
	printf("\nAll initialization and cleanup tests passed successfully!\n");
	return (0);
}
