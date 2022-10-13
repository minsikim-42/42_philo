#include "philo.h"

int	ft_strlen(char *c)
{
	int		i;

	i = 0;
	while (c[i] != 0)
	{
		i++;
	}
	return (i);
}

int	ft_atoi(char *c)
{
	int		result;
	int		i;

	i = 0;
	result = 0;
	while (i < ft_strlen(c))
	{
		result = result * 10 + (c[i] - 48);
		i++;
	}
	return (result);
}

int	what_time_isit(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec % 1000) * 1000 + (time.tv_usec / 1000);
	return (ms);
}

void	set_input(t_data *data, int argc, char *argv[])
{
	data->man = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_think = ft_atoi(argv[4]);
	if (data->man > 200 || data->t_die < 60 || \
		data->t_eat < 60 || data->t_think < 60)
	{
		printf("Input Error\n");
		return ;
	}
	data->eat_check = 0;
	data->eat_count = 0;
	data->die = 0;
	data->dmd = 0;
	data->start_time = 0;
	data->argc = argc;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->man);
}

void	set_data(t_data *data, int argc, char *argv[])
{
	int		i;

	set_input(data, argc, argv);
	if (data->man > 200 || data->t_die < 60 || \
			data->t_eat < 60 || data->t_think < 60)
		return ;
	i = 0;
	while (i < data->man)
	{
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->death), NULL);
	pthread_mutex_init(&(data->eat), NULL);
	set_philo(data);
}
