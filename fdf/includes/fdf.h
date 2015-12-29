/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 13:36:01 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 15:15:36 by vmarchau         ###   ########.fr       */
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
}					t_env;

int					parse(int const fd, t_env *env);
t_point				*lst_newpt(int x, int y, int h);
void				debug_point(t_env *env);
void				render(t_env *env);

int					onKeyPress(int keycode, void *param);

#endif
