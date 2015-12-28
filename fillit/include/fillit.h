/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:54:18 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/28 14:04:37 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BLACK			"\033[1;30m"
# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define YELLOW			"\033[1;33m"
# define BLUE			"\033[1;34m"
# define PURPLE			"\033[1;35m"
# define CYAN			"\033[1;36m"
# define GREY			"\033[1;37m"
# define BLACKB			"\033[0;30m"
# define REDB			"\033[0;31m"
# define GREENB			"\033[0;32m"
# define YELLOWB		"\033[0;33m"
# define BLUEB			"\033[0;34m"
# define PURPLEB		"\033[0;35m"
# define CYANB			"\033[0;36m"
# define GREYB			"\033[0;37m"

typedef struct			s_tris
{
	char				*color;
	char				*content;
	size_t				content_size;
	struct s_tris		*next;
	char				w;
	char				h;
	char				idx;
	char				plcx;
	char				plcy;
	char				px[4];
	char				py[4];
}						t_tris;

typedef struct			s_map
{
	char				map[16][16];
	char				w;
	char				x;
	char				y;
	int					nb;
	char				**colors;
	struct s_tris		**tab;
	int					color;
}						t_map;

t_map					*parse(int fd, int count);
int						is_char_near(char *str, char c, size_t index);
int						is_correct_form(char *str);
t_map					*verify(t_tris *lst, size_t count);
t_tris					*ft_newtris(void const *content, size_t content_size);
void					compute_index(t_tris *lst);
void					compute_position(t_tris *lst, int pos);
void					setup_map(t_map *map, int count, t_tris **tab);
void					show_map(t_map *map);
int						is_putable(t_map *map, t_tris *tris);
void					compute_size(t_tris *lst);
int						resolve(t_map *map, int i);
void					init_colors(t_map *map);
char					free_ptr(void *ptr);

#endif
