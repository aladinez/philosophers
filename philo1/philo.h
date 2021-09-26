/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:49 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/26 13:25:57 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data{
    
    pthread_mutex_t print;
    pthread_mutex_t *forks;

    unsigned long starting_time;
    int philo_num;
    int time_eat;
    int time_die;
    int time_sleep;
    int eating_times;
    
}t_data;

typedef struct s_philos{
    int last_time_eat;
    int num_of_eats;
    int index;
    t_data *data;
}t_philos;

long	ft_atoi(const char *str);
int	count_num(char str, long *num, long max, long sign);


#endif