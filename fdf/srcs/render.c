/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:13:08 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/02 13:58:39 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_env *env, int x, int y, int color)
{
	mlx_pixel_put(env->mlx, env->display,
			x + env->cursr_x / 2, y + env->cursr_y / 2, color);
}

void    draw_line(t_env *env, t_point first, t_point second, int color)
{
	int e;
	int dx;
	int dy;

	e = second.x - first.x;
	dx = e * 2;
	dy = (second.y - first.y) * 2;
	while (first.x <= second.x)
	{
		draw_pixel(env, first.x, first.y, color);
		if (dx > dy)
			first.x += 1;
		else
			first.y += 1;
		e = (dx > dy ? e - dy : e - dx);
		if (e <= 0)
		{
			if (dx > dy)
				first.y += 1;
			else
				first.x += 1;
			e = (dx > dy ? e + dx : e + dy);
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

void	render(t_env *env)
{
	t_point	*tmp;
	t_point *next;
	int		i;
	int		j;

	debug_points(env);
	tmp = env->first->next;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && tmp->index != env->size_x)
			draw_line(env, *tmp, *tmp->next, 0x33FF33);
		tmp = tmp->next;
	}
	i = 0;
	tmp = env->first->next;
	draw_line(env, *tmp, *(find_next_idx(tmp->next, i)), 0xFF0000);
	i = 0;
	while (i < env->size_x)
	{
		j = 0;
		tmp = env->first->next;
		while (j < env->size_y - 1)
		{
			next = find_next_idx(tmp->next, i);
			draw_line(env, *tmp, *next, 0x33FF33);
			tmp = next;
			j++;
		}
		i++;
	}
}
