/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:12 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/26 13:34:23 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int parsing(t_data *data, int argc, char **argv)
{
	int	i;

	if ((argc != 5 && argc != 6))
	{
		printf("Arguments Error\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
		{
			printf("Arguments error\n");
			return (0);
		}
		i++;
	}
	data->philo_num = ft_atoi(argv[1]);
	data->time_eat = ft_atoi(argv[2]);
	data->time_die = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eating_times = ft_atoi(argv[5]);
	else
		data->eating_times = -1;
	return (1);
}

t_philos	*create_philos(t_data *data)
{
	t_philos *philos;
	int	i;

	i = 0;
	philos = (t_philos *)malloc(data->philo_num * sizeof(t_philos));
	while (i < data->philo_num)
	{
		philos[i].index = i + 1;
		philos[i].data = data;
		philos[i].num_of_eats = 0;
		i++;
	}
	return (philos);
}

void	init_forks(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_init(&data->print , NULL);
	data->forks = (pthread_mutex_t *)malloc(data->philo_num * sizeof(pthread_mutex_t));
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i] , NULL);
		i++;
	}
	
}

void take_fork(t_data *data, int index)
{
	pthread_mutex_lock(&data->print);
	printf("philo num %d has taken a fork\n", index);
	pthread_mutex_unlock(&data->print);
}

void eating(t_data *data, int index)
{
	pthread_mutex_lock(&data->print);
	printf("philo num %d is eating\n", index);
	pthread_mutex_unlock(&data->print);
}

void	*routine(void *philo1)
{
	t_philos	*philo;
	int			index;
	

	philo = (t_philos *)philo1;
	index = philo->index;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[index - 1]);
		take_fork(philo->data, index);
		pthread_mutex_lock(&philo->data->forks[index]);
		take_fork(philo->data, index);


		

	}
	return (NULL);
}

void	create_threads(t_philos *philos, t_data data)
{
	pthread_t *threads;
	int	i;

	threads = (pthread_t *)malloc(data.philo_num * sizeof(pthread_t));
	i = 0;
	while (i < data.philo_num)
	{
		if (pthread_create(threads + i, NULL, &routine, (void *)(philos + i)) != 0)
		{
			printf("Error occured while creating a thread\n");
			exit(1);
		}
		i++;
	}
}

unsigned long	get_time()
{
	struct timeval timeval;
	unsigned long	time;
	
	gettimeofday(&timeval, NULL);
	time = (unsigned long) timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philos *philos;

	if (!parsing(&data, argc, argv))
		return (0);
	philos = create_philos(&data);
	init_forks(&data);
	data.starting_time = get_time();
	create_threads(philos, data);
	
	int i = 0;
	while (i < data.philo_num)
	{
		printf("philo id : %d\n", philos[i].index);
		i++;
	}
	while (1)
		;
	// init_forks(philos);
	
}