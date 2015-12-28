# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/30 22:35:18 by vmarchau          #+#    #+#              #
#    Updated: 2015/11/27 15:41:36 by vmarchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =  ft_toupper.c ft_tolower.c ft_isalpha.c ft_memalloc.c ft_memdel.c \
ft_isdigit.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_strnew.c ft_strdel.c \
ft_isascii.c ft_isprint.c ft_atoi.c ft_strstr.c ft_strclr.c ft_striter.c \
ft_strnstr.c ft_strlen.c ft_strcmp.c ft_strncmp.c ft_striteri.c ft_strmap.c \
ft_strrchr.c ft_strchr.c ft_strcat.c ft_strncat.c ft_strmapi.c ft_strequ.c \
ft_strlcat.c ft_strcpy.c ft_strncpy.c ft_strdup.c ft_strnequ.c ft_strsub.c \
ft_memcmp.c ft_memchr.c ft_memmove.c ft_memccpy.c ft_strjoin.c ft_strtrim.c \
ft_memcpy.c ft_memset.c ft_bzero.c ft_strsplit.c ft_itoa.c ft_putchar.c \
ft_putstr.c ft_putnbr.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putnbr_fd.c ft_putendl_fd.c ft_power.c ft_lstadd.c ft_lstdel.c \
ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDE = /libft.h

%.o: %.c
		gcc $(FLAGS) -I$(INCLUDE) -o $@ -c $<

all: $(NAME)

$(NAME) : $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
clean:
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(NAME)
re: fclean all
