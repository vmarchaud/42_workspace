# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 15:54:42 by vmarchau          #+#    #+#              #
#    Updated: 2015/12/18 14:43:47 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

NAME = fillit
CC = gcc
CFGLAGS = -Werror -Wextra -Wall

SRC_NAME  = main.c parser.c util.c map_util.c resolve.c
OBJ_NAME = $(SRC_NAME.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "▓██████▓▒  █▓    ██▓        ██▓        ██▓   ▓▄▄▄█████▓"
	@echo "▓██  ▒           ▓█▒        ▓█▒                  ██▒ ▒"
	@echo "▒████ ░   ▒██▒   ▒█░        ▒█░        ▒██▒      ██░ ▒░"
	@echo "░▓▒  ░    ░██░   ▒█░        ▒█░        ░██░      ██▓ ░ "
	@echo "░█░       ░██░   ░█████▓▒   ░█████▓▒   ░██░     ▒██▒ ░ "
	@echo " ▒ ░       ░▓     ░ ▒░▓  ░   ░ ▒░▓  ░   ░▓       ▒ ░░   "
	@echo " ░          ▒ ░   ░ ░ ▒  ░   ░ ░ ▒  ░    ▒ ░       ░    "
	@echo " ░ ░        ▒ ░     ░ ░        ░ ░       ▒ ░     ░      "
	@echo "            ░         ░  ░       ░  ░    ░              "
	@make -C lib/
	@$(CC) $(CFLAGS) -L./lib/ -lft $(SRC) $(INC) -o $(NAME) ./lib/libft.a $(OBJ)
	@echo "done."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(LIB) $(INC) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/

re: fclean all
