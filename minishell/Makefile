#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtarreau <vtarreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/20 14:17:44 by vtarreau          #+#    #+#              #
#    Updated: 2016/02/22 16:29:12 by vmarchau         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra -g

SRC_PATH = ./src/
SRC_NAME = 	main.c builtin_env.c builtin_utils.c env_lst.c env_util.c exec.c \
			util.c env_parse.c builtin_exit.c builtin_cd.c builtin_alias.c \
			alias_util.c alias_lst.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

INC_PATH = ./libft/includes/ ./includes/

LIB_PATH = ./libft/
LIB_NAME = ./libft/libft.a

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB_PATH)
		$(CC) $(CFLAGS) $(LIB) $(INC) -o $(NAME) $(LIB_NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			@mkdir $(OBJ_PATH) 2> /dev/null || echo "" >/dev/null
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
		rm -fv $(OBJ)
		@make -C $(LIB_PATH) clean
		@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean:
		rm -fv $(OBJ)
		rm -fv $(NAME)
		@make -C $(LIB_PATH) fclean

re: fclean all

norme:
	norminette $(SRC)
	norminette $(IN_PATH)*.h



