/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:23:53 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 18:49:32 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	timeval;
	unsigned long	time;

	gettimeofday(&timeval, NULL);
	time = (unsigned long) timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time);
}

void	take_fork(t_philos *philo, int index)
{
	int	right;

	right = (index + 1) % philo->data->philo_num;
	pthread_mutex_lock(&philo->data->forks[right]);
	pthread_mutex_lock(&philo->data->forks[index]);
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d has taken a fork\n", get_time(), index + 1);
	printf("%lu %d has taken a fork\n", get_time(), index + 1);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->eat_check);
	eating(philo, index);
	pthread_mutex_unlock(&philo->eat_check);
	pthread_mutex_unlock(&philo->data->forks[right]);
	pthread_mutex_unlock(&philo->data->forks[index]);
}

void	eating(t_philos *philo, int index)
{
	philo->last_eat = get_time();
	philo->num_of_eats++;
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is eating\n", philo->last_eat, index + 1);
	pthread_mutex_unlock(&philo->data->print);
	usleep((philo->data->time_eat - 10) * 1000);
	while (get_time() - philo->last_eat < (unsigned long)philo->data->time_eat)
		;
}

void	sleeping(t_philos *philo, int index)
{
	unsigned long	before_sleep;

	before_sleep = get_time() * 1000;
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is sleeping\n", get_time(), index + 1);
	pthread_mutex_unlock(&philo->data->print);
	usleep((philo->data->time_sleep - 10) * 1000);
	while (get_time() - before_sleep < (unsigned long)philo->data->time_sleep)
		;
}

void	thinking(t_philos *philo, int index)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d is thinking\n", get_time(), index + 1);
	pthread_mutex_unlock(&philo->data->print);
}
