/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:54 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/07/13 20:39:51 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_args{
    int philo_num;
    int *time_eat;
    int *time_die;
    char *index;
    pthread_t *philos;
    pthread_mutex_t *forks;
    int test;
}t_args;

pthread_mutex_t g_mutex;

#endif