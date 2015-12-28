# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 15:54:42 by vmarchau          #+#    #+#              #
#    Updated: 2015/12/21 13:57:36 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

NAME = alum1
CC = gcc
CFGLAGS = -Werror -Wextra -Wall

SRC_NAME  = main.c parse.c game.c
OBJ_NAME = $(SRC_NAME.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "      _        __      ______            "
	@echo "     / \      [  |   .' ___  |           "
	@echo "    / _ \      | |  / .'   \_|  __   _   "
	@echo "   / ___ \     | |  | |        [  | | |  "
	@echo " _/ /   \ \_   | |  \ '.___.'\  | \_/ |, "
	@echo "|____| |____| [___]  '.____ .'  '.__.'_/ "
	@make -C libft/
	@$(CC) $(CFLAGS) -L./libft/ -lft $(SRC) $(INC) -o $(NAME) ./libft/libft.a $(OBJ)
	@echo "AlCu done."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(LIB) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all

.PHONY: all re fclean clean
