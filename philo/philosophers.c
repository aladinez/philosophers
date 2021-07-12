/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:52 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/07/12 20:50:58 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *args2)
{
    t_args *args;
    int *id;
    int i = 0;
    
    // pthread_mutex_lock(&g_mutex);
    args = (t_args *)args2;
    while (args->index[i] == 'a')
        i++;
    args->index[i] = 'a';
    id = malloc(sizeof(int));
    *id = i + 1;
    printf("philo num %d is alive\n", *id);
    // sleep(1);
    // printf("Im alive again\n");
    // pthread_mutex_unlock(&g_mutex);
    
    return (id);
}

int main()
{
    int number_of_philosophers = 10;
    int i = 0;
    int *philo_num;
    void *ret_val;
    t_args args;
    
    args.index = (char *)malloc(number_of_philosophers * sizeof(char));
    pthread_mutex_init(&g_mutex, NULL);
    while (i < number_of_philosophers)
    {
        args.index[i] = 'a';
        i++;
    }
    // int time_to_die;
    // int time_to_eat;
    // int time_to_sleep;
    i = 0;
    pthread_t *th;

    th = (pthread_t *)malloc(number_of_philosophers * sizeof(pthread_t));

    while (i < 10)
    {
        args.index[i] = 'f';
        if (pthread_create(th + i, NULL, &routine, (void*)&args) != 0)
			return (1);
        // args.index[i] = 'a';
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(th[i], &ret_val);
        philo_num = (int *)ret_val;
        printf("philo num %d is done\n", *philo_num);
        free(philo_num);
		i++;
    }
    return (0);
}