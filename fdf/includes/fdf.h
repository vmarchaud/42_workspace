/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 13:36:01 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/05 15:38:45 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

typedef struct		s_point
{
	int				x;
	int				y;
	int				h;
	size_t			index;
	struct s_point	*next;
}					t_point;

typedef struct		s_env
{
	int				win_x;
	int				win_y;

	t_point			orient;
	t_point			*first;

	void			*mlx;
	void			*display;

	int				cursr_x;
	int				cursr_y;
	int				zoom;
	int				diff;

	int				size_x;
	int				size_y;
}					t_env;

int					parse(int const fd, t_env *env);
t_point				*lst_newpt(int x, int y, int h, int index);
void				debug_points(t_env *env);
void				debug_point(t_point *point);
void				render(t_env *env);
void				compute_positon(t_env *env, int oldzoom, int olddiff);

int					onKeyPress(int keycode, void *param);

#endif
