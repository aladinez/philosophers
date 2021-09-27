/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:12 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 19:05:24 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo1)
{
	t_philos	*philo;

	philo = (t_philos *)philo1;
	while (1)
	{
		take_fork(philo, philo->index);
		sleeping(philo, philo->index);
		thinking(philo, philo->index);
	}
	return (NULL);
}

int	check_eat_times(t_philos *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (philos[i].num_of_eats < data->eating_times)
			return (0);
		i++;
	}
	return (1);
}

void	supervisor(t_philos *philos, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&philos[i].eat_check);
			if ((philos[i].last_eat
					+ (unsigned long)data->time_die) < get_time())
			{
				pthread_mutex_lock(&data->print);
				printf("%lu %d died\n", get_time(), philos[i].index + 1);
				return ;
			}
			pthread_mutex_unlock(&philos[i].eat_check);
			i++;
		}
		if (data->eating_times > 0 && check_eat_times(philos, data))
			exit(1);
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philos;

	data = (t_data *)malloc(sizeof(t_data));
	if (!parsing(data, argc, argv))
		return (0);
	philos = create_philos(data);
	create_threads(philos, data);
	supervisor(philos, data);
	free(data->forks);
	free(data);
	free(philos);
	return (0);
}
