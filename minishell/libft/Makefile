# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 15:54:42 by vmarchau          #+#    #+#              #
#    Updated: 2016/02/24 14:31:52 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

NAME = libft.a
CC = gcc
CFGLAGS = -Werror -Wextra -Wall

SRC_NAME  = ft_toupper.c ft_tolower.c ft_isalpha.c ft_memalloc.c ft_memdel.c \
			ft_isdigit.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_strnew.c \
			ft_strdel.c ft_isascii.c ft_isprint.c ft_atoi.c ft_strstr.c \
			ft_strclr.c ft_striter.c ft_strnstr.c ft_strlen.c ft_strcmp.c \
			ft_strncmp.c ft_striteri.c ft_strmap.c ft_strrchr.c ft_strchr.c \
			ft_strcat.c ft_strncat.c ft_strmapi.c ft_strequ.c ft_strlcat.c \
			ft_strcpy.c ft_strncpy.c ft_strdup.c ft_strnequ.c ft_strsub.c \
			ft_memcmp.c ft_memchr.c ft_memmove.c ft_memccpy.c ft_strjoin.c \
			ft_strtrim.c ft_memcpy.c ft_memset.c ft_bzero.c ft_strsplit.c \
			ft_itoa.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
			ft_putchar_fd.c ft_putstr_fd.c  ft_putnbr_fd.c ft_putendl_fd.c \
			ft_power.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
			ft_lstmap.c ft_lstnew.c ft_count_char.c ft_strfind.c ft_isnumeric.c \
			ft_strlen_bfr_char.c ft_lstpush_back.c get_next_line.c \
			strreplace_once.c ft_replace_char.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "libft done."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(LIB) $(INC) -o $@ -c $<
	@echo "\033[A\033[K\033[A"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)
