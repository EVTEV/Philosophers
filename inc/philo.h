#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_philo 
{
	int				id;
	int				nbr_meal;
	long long		time_meal;
    pthread_t		thread;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct	s_table
{
	int				num_philo;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_table;


//----------init----------//
//-----init_room.c-----//
t_table	*init_table(int num_philo);

//----------meal----------//
//-----sart_meal.c-----//
long long	get_time(void);
void		*start_meal(void *args);
void		*dead_philo(void *args);

//----------utils----------//
//-----utils.c-----//
char	msg_error(char *msg);

#endif

