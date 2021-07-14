/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:54 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/07/14 20:48:29 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_args{
    int philo_num;
    int time_eat;
    int time_die;
    int time_sleep;
    int last_time_eat;
    char *index;
    pthread_t *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int test;
}t_args;


int get_index(t_args *args);
void *routine(void *args2);
void    init_forks(t_args *args);
void create_thread(t_args *args);


#endif