/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:04:12 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/24 11:12:46 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Arguments Error\n");
        return (0);
    }
    else
    {
        data->philo_num = ft_atoi(argv[1]);
        data->time_eat = ft_atoi(argv[2]);
        data->time_die = ft_atoi(argv[3]);
        data->time_sleep = ft_atoi(argv[4]);
        if (argc == 6)
            data->eating_times = ft_atoi(argv[5]);
        else
            data->eating_times = -1;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data  data;

    if (!parsing(&data, argc, argv))
        return (0);
    
}