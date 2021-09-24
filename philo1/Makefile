# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 10:07:26 by aez-zaou          #+#    #+#              #
#    Updated: 2021/09/24 11:13:59 by aez-zaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

GCC			= gcc -Wall -Wextra -Werror -pthread
SRCS		= philo.c	\
			ft_atoi.c	\

all : $(NAME)

$(NAME) : $(SRCS)
		$(GCC) $(SRCS) -o $(NAME)

clean :
		rm -f $(NAME)

fclean : clean

re: fclean all