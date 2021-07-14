/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:52 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/07/14 21:02:26 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
int get_index(t_args *args)
{
    int i;

    i = 0;
    while (args->index[i] == 'a')
        i++;
    args->index[i] = 'a';
    return (i);
}

void take_fork(t_args *args, int id)
{
    pthread_mutex_lock(&args->print);
    printf("philo num %d has taken a fork\n", id + 1);
    pthread_mutex_unlock(&args->print);
}

void thinking(t_args *args, int id)
{
    pthread_mutex_lock(&args->print);
    printf("philo num %d is thinking\n", id + 1);
    pthread_mutex_unlock(&args->print);
}
void sleeping(t_args *args, int id)
{

    pthread_mutex_lock(&args->print);
    printf("philo num %d is sleeping\n", id + 1);
    pthread_mutex_unlock(&args->print);
    usleep(args->time_sleep * 1000);
}

void eating(t_args *args, int id)
{

    pthread_mutex_lock(&args->print);
    printf("philo num %d  is eating...\n", id + 1);
    pthread_mutex_unlock(&args->print);
    usleep(args->time_eat * 1000);
}

void *routine(void *args2)
{
    t_args *args;
    int id;
    int i;
    
    args = (t_args *)args2;
    id = get_index(args);
    
    while (1)
    {
        pthread_mutex_lock(&args->forks[id]);
        take_fork(args, id);
        pthread_mutex_lock(&args->forks[(id + 1) % args->philo_num]);
        take_fork(args, id);
        
        eating(args, id);

        pthread_mutex_unlock(&args->forks[id]);
        pthread_mutex_unlock(&args->forks[(id + 1) % args->philo_num]);
        
        sleeping(args, id);
        
        

    }
    return (NULL);
}

int main()
{
    int i;
    t_args args;
    
    args.philo_num = 6;
    args.time_eat = 100;
    args.time_die = 400;
    args.time_sleep = 200;
    args.index = (char *)malloc(args.philo_num * sizeof(char));
    memset(args.index, 'a', args.philo_num);
    init_forks(&args);

    create_thread(&args);
   

    
    return (0);
}

void    init_forks(t_args *args)
{
    int i;

    i = 0;
    pthread_mutex_init(&args->print , NULL);
    args->forks = (pthread_mutex_t *)malloc(args->philo_num * sizeof(pthread_mutex_t));
    while (i < args->philo_num)
    {
        pthread_mutex_init(&args->forks[i] , NULL);
        i++;
    }
}

void create_thread(t_args *args)
{
    int i;

    args->philos = (pthread_t *)malloc(args->philo_num * sizeof(pthread_t));
    i = 1;
    while (i < 10)
    {
        args->index[i] = 'f';
        if (pthread_create(args->philos + i, NULL, &routine, (void*)args) != 0)
		{
            printf("Error occured while creating a thread\n");
			exit(1);
        }
        i += 2;
    }
    sleep(1);
    i = 0;
    while (i < 10)
    {
        args->index[i] = 'f';
        if (pthread_create(args->philos + i, NULL, &routine, (void*)args) != 0)
        {
            printf("Error occured while creating a thread\n");
			exit(1);
        }
        i += 2;
    }
    i = 1;
    while (i < 10)
    {
        pthread_join(args->philos[i], NULL);
        i += 2;

    }
    i = 0;
    while (i < 10)
    {
        pthread_join(args->philos[i], NULL);
        i += 2;
    }
}