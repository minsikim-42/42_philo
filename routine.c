#include "philo.h"

void	set_philo(t_data *data)
{
	int		i;

	data->philo = malloc(sizeof(t_data) * data->man);
	i = 0;
	while (i < data->man)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->man;
		data->philo[i].data = data;
		data->philo[i].eaten = 0;
		data->philo[i].eat_time = what_time_isit();
		i++;
	}
}

int	mutex_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->fork[philo->left_fork]));
	printf("[%d] %d: left_fork\n", what_time_isit(), philo->id);
	while (data->man == 1 && !(check_die(data)))
	{
		printf("기다리는듕..\n");
		usleep(100000);
	}
	if (data->die == 1)
		return (0);
	pthread_mutex_lock(&(data->fork[philo->right_fork]));
	printf("[%d] %d: right_fork\n", what_time_isit(), philo->id);
	return (1);
}

void	mutex_eat(t_data *v_data, t_philo *philo, long long *time_now)
{
	t_data	*data;

	data = v_data;
	pthread_mutex_lock(&data->eat);
	philo->eaten++;
	data->eat_check = eat_check(philo);
	printf("estcheck -%d-\n", data->eat_check);
	pthread_mutex_unlock(&data->eat);
	*time_now = philo->eat_time;
	philo->eat_time = what_time_isit();
	while (!(data->die))
	{
		*time_now = what_time_isit();
		if (*time_now - philo->eat_time >= data->t_eat)
		{
			printf("[%d] %d:ㅂㅓ억~ (%d)\n", \
				what_time_isit(), philo->id, philo->eaten);
			break ;
		}
		usleep(10);
	}
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*ft_routine(void *v_philo)
{
	t_philo		*philo;
	long long	time_now;

	philo = v_philo;
	if (philo->id % 2)
		usleep(1000);
	while (!(philo->data->die) && !(philo->data->eat_check))
	{
		if (mutex_fork(philo->data, philo) == 0)
			break ;
		mutex_eat(philo->data, philo, &time_now);
		philo->think_time = what_time_isit();
		while (!(philo->data->die))
		{
			time_now = what_time_isit();
			if (time_now - philo->think_time >= philo->data->t_think)
			{
				printf("[%d]생각했따\n", what_time_isit());
				break ;
			}
			usleep(10);
		}
	}
	return (NULL);
}
