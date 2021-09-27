/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:54:16 by aez-zaou          #+#    #+#             */
/*   Updated: 2021/09/27 17:36:18 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assing_values(t_data *data, int argc, char **argv)
{
	(data)->philo_num = ft_atoi(argv[1]);
	(data)->time_die = ft_atoi(argv[2]);
	(data)->time_eat = ft_atoi(argv[3]);
	(data)->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		(data)->eating_times = ft_atoi(argv[5]);
		if ((data)->eating_times == 0)
			exit(1);
	}
	else
		(data)->eating_times = -1;
}

int	parsing(t_data *data, int argc, char **argv)
{
	int	i;

	if ((argc != 5 && argc != 6))
	{
		printf("Arguments Error\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
		{
			printf("Arguments error\n");
			return (0);
		}
		i++;
	}
	assing_values(data, argc, argv);
	return (1);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	long	sign;
	long	num;
	long	max;

	num = 0;
	max = 9223372036854775807;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str != 0 && (*str >= 48 && *str <= 57))
	{
		if (count_num(*str, &num, max, sign))
			break ;
		str++;
	}
	return (sign * num);
}

int	count_num(char str, long *num, long max, long sign)
{
	if (*num <= (max - (str - 48)) / 10)
		*num = *num * 10 + (str - 48);
	else
	{
		if (sign == 1)
			*num = -1;
		else
			*num = 0;
		return (1);
	}
	return (0);
}
