# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 07:28:35 by pcatapan          #+#    #+#              #
#    Updated: 2022/03/24 06:13:58 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = ./src/*.c ./PRINTF/*.c ./src/move_element/*.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

KIT = -l mlx -framework openGL -framework AppKit


$(NAME) :
	$(CC) -g $(SRCS) $(KIT)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -rf $(NAME) 
	rm -rf a.*
	rm -rf *.dSYM

norm:
	norminette -R ./src/*.c ./PRINTF
