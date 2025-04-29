#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct	s_fork 
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork

typedef struct	s_philo 
{
	struct s_data	*data;
	int				id;
	int				meal_eat;
	long long		time_meal;
    pthread_t		thread;
	t_state			state;
    t_fork			*left_fork;
    t_fork			*right_fork;
}	t_philo;

typedef struct	s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meal;
	bool			meal_stop;
	long long		start;
	t_fork;			*forks;
	t_philo;		*philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
}	t_data;



// --------------- init.c --------------- //
int	init_data(t_data *data, int ac, char *av);
int	init_mutex(t_data *data);
int	init_fork(t_data *data);
int	init_philo(t_data *data);

// --------------- clean.c --------------- //
void	clean_resource(t_data *data);

// --------------- utils.c --------------- //
int	ft_atoi(const char *str);

#endif

