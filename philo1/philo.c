/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:12 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 10:35:59 by aez-zaou         ###   ########.fr       */
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
	(data)->philo_num = ft_atoi(argv[1]);
	(data)->time_die = ft_atoi(argv[2]);
	(data)->time_eat = ft_atoi(argv[3]);
	(data)->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(data)->eating_times = ft_atoi(argv[5]);
	else
		(data)->eating_times = -1;
	return (1);
}

unsigned long	get_time()
{
	struct timeval timeval;
	unsigned long	time;
	
	gettimeofday(&timeval, NULL);
	time = (unsigned long) timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time);
}

t_philos	*create_philos(t_data *data)
{
	t_philos *philos;
	
	int	i;

	i = 0;
	pthread_mutex_init(&data->print , NULL);
	data->forks = (pthread_mutex_t *)malloc(data->philo_num * sizeof(pthread_mutex_t));
	philos = (t_philos *)malloc(data->philo_num * sizeof(t_philos));
	while (i < data->philo_num)
	{
		philos[i].num_of_eats = 0;
		pthread_mutex_init(&data->forks[i] , NULL);
		i++;
	}
	return (philos);
}

// void	init_forks(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	pthread_mutex_init(&data->print , NULL);
// 	data->forks = (pthread_mutex_t *)malloc(data->philo_num * sizeof(pthread_mutex_t));
// 	while (i < data->philo_num)
// 	{
		
// 		i++;
// 	}
	
// }

void take_fork(t_philos *philo, int index)
{
	int left = index;
	int right = (left + 1) % philo->data->philo_num;
	
	pthread_mutex_lock(&philo->data->forks[right]);	
	pthread_mutex_lock(&philo->data->forks[left]);
	
	pthread_mutex_lock(&philo->data->print);
	printf("%lu philo num %d has taken a fork %d\n", get_time() - philo->data->starting_time, index, right);
	printf("%lu philo num %d has taken a fork %d\n", get_time() - philo->data->starting_time, index, left);
	pthread_mutex_unlock(&philo->data->print);


	eating(philo, index);


	pthread_mutex_unlock(&philo->data->forks[right]);
	pthread_mutex_unlock(&philo->data->forks[index]);
	
}

void eating(t_philos *philo, int index)
{
	philo->last_eat = get_time();
	pthread_mutex_lock(&philo->data->print);
	printf("%lu philo num %d is eating ===> %d times\n", philo->last_eat - philo->data->starting_time, index, philo->num_of_eats);
	pthread_mutex_unlock(&philo->data->print);
	
	usleep(philo->data->time_eat * 1000);



	philo->num_of_eats++;
	
}

void	sleeping(t_philos *philo, int index)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu philo num %d is sleeping\n", get_time() - philo->data->starting_time, index);
	pthread_mutex_unlock(&philo->data->print);

	usleep(philo->data->time_sleep * 1000);
}

void thinking(t_philos *philo, int index)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu philo num %d is thinking\n", get_time() - philo->data->starting_time, index);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *philo1)
{
	t_philos	*philo;
	

	philo = (t_philos *)philo1;
	while (1)
	{
		take_fork(philo, philo->index);

		// eating(philo, philo->index);
		sleeping(philo, philo->index);
		thinking(philo, philo->index);

	}
	return (NULL);
}

void	create_threads(t_philos *philos, t_data *data)
{
	int	i;

	i = 0;
	data->starting_time = get_time();
	while (i < data->philo_num)
	{
		philos[i].index = i;
		philos[i].data = data;
		if (pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]) != 0)
		{
			printf("Error occured while creating a thread\n");
			exit(1);
		}
		i += 2;
	}

	usleep(2000);
	
	i = 1;
	while (i < data->philo_num)
	{
		philos[i].index = i;
		philos[i].data = data;
		if (pthread_create(&philos[i].thread, NULL, &routine, (void *)&philos[i]) != 0)
		{
			printf("Error occured while creating a thread\n");
			exit(1);
		}
		i+=2;
	}

}



int main(int argc, char **argv)
{
	t_data  *data;
	t_philos *philos;

	data = (t_data *)malloc(sizeof(t_data));

	if (!parsing(data, argc, argv))
		return (0);
	philos = create_philos(data);
	create_threads(philos, data);
	
	while (1)
		;	
}