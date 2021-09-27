# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 10:07:26 by aez-zaou          #+#    #+#              #
#    Updated: 2021/09/27 17:52:18 by aez-zaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

GCC			= gcc -Wall -Wextra -Werror -pthread -fsanitize=address
SRCS		= philo.c	\
			utils.c		\
			events.c	\
			threads.c	\

all : $(NAME)

$(NAME) : $(SRCS)
		$(GCC) $(SRCS) -o $(NAME)

clean :
		rm -f $(NAME)

fclean : clean

re: fclean all