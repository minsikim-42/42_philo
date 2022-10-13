#include "philo.h"

int	eat_check(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->argc == 6)
	{
		if (philo->eaten >= data->eat_count)
		{
			if (data->dmd == 0)
			{
				printf("다무따\n");
				data->eat_check = 1;
				data->dmd = 1;
				return (1);
			}
			return (1);
		}
	}
	return (0);
}

int	check_die(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->man)
	{
		if (what_time_isit() - data->philo[i].eat_time > data->t_die)
		{
			data->die = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	die_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->eat_check))
	{
		i = 0;
		while (i < data->man && !(data->die))
		{
			pthread_mutex_lock(&(data->eat));
			if (what_time_isit() - philo[i].eat_time > data->t_die)
			{
				printf("죽어부러따(%d)\n", i);
				data->die = 1;
			}
			pthread_mutex_unlock(&(data->eat));
			i++;
		}
		if (data->die == 1)
			break ;
	}
}

void	start(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*input;

	input = (void *)(philo);
	data->start_time = what_time_isit();
	i = 0;
	while (i < data->man)
	{
		pthread_create(&(philo[i].thread), NULL, ft_routine, &input[i]);
		i++;
	}
	die_check(data, philo);
	i = 0;
	while (i < data->man)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < data->man)
		pthread_mutex_destroy(&(data->fork[i++]));
	free(data->philo);
	free(data->fork);
	pthread_mutex_destroy(&(data->eat));
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 6 && argc != 5)
	{
		printf("Input Error\n");
		return (-1);
	}
	set_data(&data, argc, argv);
	if (data.man > 200 || data.t_die < 60 || \
			data.t_eat < 60 || data.t_think < 60)
	{
		printf("man:%d, die:%d, eat:%d, think:%d\n", \
			data.man, data.t_die, data.t_eat, data.t_think);
		return (-1);
	}
	start(&data, data.philo);
}
