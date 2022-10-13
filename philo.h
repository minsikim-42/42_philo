#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		eat_time;
	long long		think_time;
	int				eaten;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				man;
	int				t_die;
	int				t_eat;
	int				t_think;
	long long		start_time;
	int				eat_count;
	int				die;
	int				eat_check;
	int				argc;
	int				dmd;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	death;
}				t_data;

void	set_philo(t_data *data);
int		mutex_fork(t_data *data, t_philo *philo);
void	mutex_eat(t_data *data, t_philo *philo, long long *time_now);
void	*ft_routine(void *v_philo);

int		ft_strlen(char *c);
int		ft_atoi(char *c);
int		what_time_isit(void);
void	set_input(t_data *data, int argc, char *argv[]);
void	set_data(t_data *data, int argc, char *argv[]);

void	die_check(t_data *data, t_philo *philo);
int		eat_check(t_philo *philo);
int		check_die(t_data *data);
void	start(t_data *data, t_philo *philo);

#endif