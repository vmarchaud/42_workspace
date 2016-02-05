# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/11 12:36:55 by vmarchau          #+#    #+#              #
#    Updated: 2016/02/05 12:31:35 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
INC_LIBFT_PATH = ./libft/includes/
LIB_PATH = ./libft/

NAME = ft_ls
CC = gcc
CFLAGS = -Werror -Wextra -Wall

SRC_NAME = main.c parse.c lst_util.c compute.c util.c sort_file.c sort_paths.c\
		   stat.c stat2.c show.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft.a

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
INC_LIBFT = $(addprefix -I,$(INC_LIBFT_PATH))
LIB = $(LIB_PATH)$(LIB_NAME)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(LIB) $(INC_LIBFT) $(INC) $(OBJ) -o $(NAME)
	@echo $(NAME) "done."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC_LIBFT) $(INC) -o $@ -c $<
	@echo "\033[A\033[K\033[A"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
