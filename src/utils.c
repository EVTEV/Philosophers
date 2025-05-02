#include "../inc/philo.h"

//================================ UTILS =================================//
/* Convert string to integer (simple atoi implementation) */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* Get current time in milliseconds */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Calculate time difference between two timestamps */
long long	time_diff(long long past, long long present)
{
	return (present - past);
}

/* Sleep for a precise amount of time in milliseconds */
void	precise_sleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
}

/* Print philosopher status message with timestamp */
void	print_status(t_philo *philo, char *status)
{
	long long	current_time;
	t_data		*data;
	bool		should_stop;

	data = philo->data;
	pthread_mutex_lock(&data->dead_mutex);
	should_stop = data->stop_all;
	pthread_mutex_unlock(&data->dead_mutex);
	if (should_stop)
		return ;
	current_time = get_time() - data->start;
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&data->print_mutex);
}
