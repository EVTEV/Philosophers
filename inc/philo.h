/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:29:17 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 11:29:17 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_philo
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

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meal;
	bool			stop_all;
	long long		start;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitor_thread;
}	t_data;

// --------------- init.c --------------- //
int		init_data(t_data *data, int ac, char **av);
int		init_mutex(t_data *data);
int		init_fork(t_data *data);

// --------------- init_philo.c --------------- //
int		init_philo(t_data *data);

// --------------- process.c --------------- //
int		create_philo(t_data *data);
int		create_monitor(t_data *data);
int		join_philo(t_data *data);
int		start_routine(t_data *data);

// --------------- routine.c --------------- //
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*philo_routine(void *arg);
// --------------- routine_utils.c --------------- //
bool	check_stop_condition(t_philo *philo);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
bool	has_eaten_enough(t_philo *philo);

// --------------- monitor.c --------------- //
void	*monitor_routine(void *arg);

// --------------- clean.c --------------- //
void	cleanup(t_data *data);

// --------------- utils.c --------------- //
long long	get_time(void);
long long	time_diff(long long past, long long present);
void		precise_sleep(long long time);
void		print_status(t_philo *philo, char *status);

// --------------- libft_utils.c --------------- //
int		ft_atoi(const char *str);
int		msg_error(char *msg);

#endif
