/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:52 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/07/13 21:25:17 by aez-zaou         ###   ########.fr       */
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

void *routine(void *args2)
{
    t_args *args;
    int id;
    int i;
    
    args = (t_args *)args2;
    id = get_index(args);
    pthread_mutex_lock(&args->forks[id]);
    printf("philo num %d is alive\n", id);




    pthread_mutex_unlock(&args->forks[id]);
    return (NULL);
}

int main()
{
    int number_of_philosophers = 10;
    int i = 0;
    int *philo_num;
    void *ret_val;
    t_args args;
    
    args.test = 0;
    args.philo_num = 10;
    args.index = (char *)malloc(number_of_philosophers * sizeof(char));
    init_forks(&args);
    while (i < number_of_philosophers)
    {
        args.index[i] = 'a';
        i++;
    }
    // int time_to_die;
    // int time_to_eat;
    // int time_to_sleep;
    i = 0;

    create_thread(&args);
   

    
    return (0);
}

void    init_forks(t_args *args)
{
    int i;

    i = 0;
    args->forks = (pthread_mutex_t *)malloc(args->philo_num * sizeof(pthread_mutex_t));
    while (i < args->philo_num)
    {
        pthread_mutex_init(&args->forks[i] , NULL);

    }
}

void create_thread(t_args *args)
{
    args->philos = (pthread_t *)malloc(args->philo_num * sizeof(pthread_t));
    while (i < 10)
    {
        args.index[i] = 'f';
        if (pthread_create(args->philos + i, NULL, &routine, (void*)args) != 0)
			return (1);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(args->philos[i], NULL);
		i++;
    }
    printf("test = %d\n", args.test);
}