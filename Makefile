# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 20:19:53 by vkuzmin           #+#    #+#              #
#    Updated: 2023/08/09 18:29:58 by vkuzmin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

id = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC  =  srcs/main.c srcs/utils.c srcs/init.c srcs/threads.c srcs/actions.c

OBJ = $(patsubst %.c,%.o,$(SRC))
INCLUDES = /inc/philo.h

all : $(id)

$(id) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(id)

%.o : %.c $(INCLUDES)
	gcc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(id)
	
re : fclean all

.PHONY : all clean fclean re