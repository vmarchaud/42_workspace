/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:13:08 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/07 11:54:53 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void		draw_pixel(t_env *env, int x, int y, int color)
{
	mlx_pixel_put(env->mlx, env->display, x + env->cursr_x,
			(y + env->cursr_y) / sqrt(3), color);
}

void		draw_line(t_env *env, t_point p, t_point p1, int color)
{
	t_point		d;
	t_point		s;
	int			err;
	int			e2;

	d.x = abs((p1.x - p.x));
	d.y = abs((p1.y - p.y));
	s.x = (p.x < p1.x ? 1 : -1);
	s.y = (p.y < p1.y ? 1 : -1);
	err = d.x - d.y;
	while (p.x != p1.x || p.y != p1.y)
	{
		draw_pixel(env, p.x, p.y, color);
		e2 = 2 * err;
		if (e2 > -d.y)
		{
			err -= d.y;
			p.x += s.x;
		}
		if (e2 < d.x)
		{
			err += d.x;
			p.y += s.y;
		}
	}
}

t_point		*find_next_idx(t_point *strt, int idx)
{
	while (strt != NULL)
	{
		if (strt->index == idx)
			return (strt);
		strt = strt->next;
	}
	return (NULL);
}

void		render(t_env *env)
{
	t_point	*tmp;
	t_point *next;

	tmp = env->first->next;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && tmp->index + 1 == tmp->next->index)
			draw_line(env, *tmp, *tmp->next, 0x33FF33);
		next = find_next_idx(tmp->next, tmp->index);
		if (next != NULL)
			draw_line(env, *tmp, *next, 0x33FF33);
		tmp = tmp->next;
	}
}
