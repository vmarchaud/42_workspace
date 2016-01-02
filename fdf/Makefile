# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 15:54:42 by vmarchau          #+#    #+#              #
#    Updated: 2016/01/01 15:15:08 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
LIB_PATH = ./libft/
LIB_CMD = -lft

NAME = fdf
CC = gcc
CFGLAGS = -Werror -Wextra -Wall 
MLX = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

SRC_NAME  = main.c parse.c render.c util.c listener.c
OBJ_NAME = $(SRC_NAME.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L,$(LIB_PATH))

all: $(NAME)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	@echo “salut”
	$(CC) $(CFLAGS) $(LIB) $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(MLX) $(LIB) $(LIB_CMD) $(SRC) $(INC) -o $(NAME) $(OBJ)
	@echo "Fdf done."

$(OBJ_PATH):

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
