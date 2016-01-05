/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:48:05 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/05 15:54:21 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	refresh(t_env *env, int oldzoom, int olddiff)
{
	mlx_clear_window(env->mlx, env->display);
	compute_position(env, oldzoom, olddiff);
	render(env);
}

int		onKeyPress(int key, void *param)
{
	t_env *env;
	int		tmp[2];

	env = (t_env *)param;
	ft_putstr("KEYCODE ");
	ft_putnbr(key);
	ft_putendl("");

	if (key == 53 || key == 12)
	{
		mlx_destroy_window(env->mlx, env->display);
		exit(0);
	}
	tmp[0] = env->zoom;
	tmp[1] = env->diff;
	env->cursr_x = key == 123 ? env->cursr_x -= 10 : env->cursr_x;
	env->cursr_x = key == 124 ? env->cursr_x += 10 : env->cursr_x;
	env->cursr_y = key == 126 ? env->cursr_y -= 10 : env->cursr_y;
	env->cursr_y = key == 125 ? env->cursr_y += 10 : env->cursr_y;
	env->zoom = key == 69 ? env->zoom += 1 : env->zoom;
	env->zoom = key == 78 ? env->zoom -= 1 : env->zoom;
	if (key == 123 || key == 124 || key == 125 || key == 126 || key == 121
			|| key == 116 || key == 69 || key == 78)
		refresh(env, tmp[0], tmp[1]);
	return (0);
}
