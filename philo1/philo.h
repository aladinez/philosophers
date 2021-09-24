/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:49 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/24 11:15:44 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_philo{
    int last_time_eat;
    int num_of_eats;
    
    
}t_philo;

typedef struct s_data{
    int philo_num;
    int time_eat;
    int time_die;
    int time_sleep;
    int eating_times;
    
    char *index;
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int test;
}t_data;

long	ft_atoi(const char *str);
int	count_num(char str, long *num, long max, long sign);


#endif