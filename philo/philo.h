/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:49 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 17:08:06 by aez-zaou         ###   ########.fr       */
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

    int philo_num;
    int time_eat;
    int time_die;
    int time_sleep;
    int eating_times;
    int num_of_eats;

    
}t_data;

typedef struct s_philos{
    unsigned long last_eat;
    int num_of_eats;
    int index;
    pthread_t thread;
    pthread_mutex_t eat_check;
    t_data *data;
}t_philos;

long	ft_atoi(const char *str);
int	count_num(char str, long *num, long max, long sign);
int	is_digit(char *str);
int parsing(t_data *data, int argc, char **argv);
unsigned long	get_time();
t_philos	*create_philos(t_data *data);
void take_fork(t_philos *philo, int index);
void eating(t_philos *philo, int index);
void	*routine(void *philo1);
void	every_other_thread(t_philos *philos, t_data *data, int i);




#endif