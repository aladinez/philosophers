/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:41:47 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 17:48:50 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*create_philos(t_data *data)
{
	t_philos	*philos;
	int			i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	data->forks = (pthread_mutex_t *)malloc(data->philo_num
			* sizeof(pthread_mutex_t));
	philos = (t_philos *)malloc(data->philo_num * sizeof(t_philos));
	while (i < data->philo_num)
	{
		philos[i].num_of_eats = 0;
		pthread_mutex_init(&philos[i].eat_check, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (philos);
}

void	create_threads(t_philos *philos, t_data *data)
{
	every_other_thread(philos, data, 0);
	usleep(1000);
	every_other_thread(philos, data, 1);
}

void	every_other_thread(t_philos *philos, t_data *data, int i)
{
	while (i < data->philo_num)
	{
		philos[i].index = i;
		philos[i].data = data;
		philos[i].last_eat = get_time();
		if (pthread_create(&philos[i].thread, NULL, &routine
				, (void *)&philos[i]) != 0)
		{
			printf("Error occured while creating a thread\n");
			exit(1);
		}
		i += 2;
	}
}
