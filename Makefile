# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/31 11:42:23 by sbalcort          #+#    #+#              #
#    Updated: 2017/10/04 12:37:09 by sbalcort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1.exe

CC = gcc

FLAGS = -Wall -Werror -Wextra

LIBS =	-I libs/minilibx -L libs/minilibx -lmlx \
		-I libs/libft -L libs/libft -lft

SRCS =	sources/main.c \
		sources/color.c \
		sources/ray.c \
		sources/mlx_functions.c \
		sources/vector.c \
		sources/hit_list.c \
		sources/sphere.c \
		sources/camera.c \
		sources/material.c \
		sources/rectangle.c \
		sources/point_math.c

OBJS = $(SRCS:.c=.o)

INC = includes/

FRAMEWORKS = -framework OpenGl -framework AppKit

all: $(NAME)
	$(CC) -O3 $(FLAGS) -o $(NAME) $(SRCS) -I /includes $(LIBS) $(FRAMEWORKS) 

$(NAME):
	make -C libs/libft
	make -C libs/minilibx

debug:
	$(CC) -g $(FLAGS) -o $(NAME) $(SRCS) -I. $(LIBS) $(FRAMEWORKS)

clean:
	/bin/rm -f rm $(NAME)
	make -C libs/libft/ clean
	make -C libs/minilibx/ clean

fclean: clean
	/bin/rm -f rm $(NAME)
	make -C libs/libft/ fclean
	make -C libs/minilibx/ clean

re: fclean all

new: all
	./$(NAME)


# gcc -Wall -Wextra -Werror  -framework OpenGL -framework AppKit sources/main.c