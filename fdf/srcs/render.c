/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:13:08 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/30 16:06:38 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_env *env, t_point *first, t_point *second)
{
    int i;
	int tmpx;
	int tmpy;
    
    i = 0;
	tmpx = first->x;
	tmpy = first->y;
	while (tmp->x != second->x)
	{
    	mlx_pixel_put(env->mlx, env->display,  tmpx + env->cursr_x + x * 10,
                  tmp->y + env->cursr_y + y * 10, i + y);
	}
}

void	render(t_env *env)
{
	t_point	*tmp;
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 3093198;
	tmp = env->first->next;
	while (tmp != NULL)
	{
		if (x < env->line_len)
		{
			
            x++;
		}
		else
		{
			x = 0;
			y++;
		}
		tmp = tmp->next;
	}
}
