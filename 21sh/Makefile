# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/16 15:01:51 by vmarchau          #+#    #+#              #
#    Updated: 2016/03/30 13:19:43 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
CFLAGS = -Werror -Wall -Wextra

SRC_PATH = ./src/
SRC_NAME = 	main.c builtin_env.c builtin_utils.c env_lst.c env_util.c exec.c \
			util.c env_parse.c builtin_exit.c builtin_cd.c builtin_alias.c \
			alias_util.c alias_lst.c evaluate.c termcaps.c util_cursor.c \
			handle_input.c history_lst.c handle_input_2.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

INC_PATH = ./libft/includes/ ./includes/

LIB_PATH = ./libft/
LIB_NAME = ./libft/libft.a
TERMCAPS = -lncurses

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(LIB_PATH):
		@make -C $(LIB_PATH)

$(NAME): $(OBJ) $(LIB_PATH)
		@$(CC) $(TERMCAPS) $(CFLAGS) $(LIB) $(INC) -o $(NAME) $(LIB_NAME) $(OBJ)
		@echo $(NAME) "done."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || echo "" >/dev/null
		$(CC) $(CFLAGS) $(INC) -o $@ -c $<
		@echo "\033[A\033[K\033[A"

clean:
		@rm -rf $(OBJ)
		@make -C $(LIB_PATH) clean
		@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean:
		@rm -rf $(OBJ)
		@rm -rf $(NAME)
		@make -C $(LIB_PATH) fclean

re: fclean all

norme:
	norminette $(SRC)
	norminette $(IN_PATH)*.h

.PHONY: clean re all fclean norme $(LIB_PATH)
