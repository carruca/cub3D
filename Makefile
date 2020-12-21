# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/16 12:43:15 by tsierra-          #+#    #+#              #
#    Updated: 2020/12/08 11:44:15 by tsierra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = raycaster.c \
	  cub3D.c \
	  cub3D_main.c
OBJ = $(SRC:.c=.o)
LIBFTDIR = libft/
MLXDIR = mlx/

CC = gcc
CFLAGS = -Wall -Wextra #-g3 -fsanitize=address #-Werror
LINKS = -I $(LIBFTDIR) -L $(LIBFTDIR) \
		-I $(MLXDIR) -L $(MLXDIR) \
		-lmlx -framework OpenGL -framework AppKit
MAKE = make
RM = rm -f

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(MLXDIR)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(LINKS) $(LIBFTDIR)libft.a 

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all
