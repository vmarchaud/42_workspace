/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:48:05 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/04 16:04:23 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		onKeyPress(int keycode, void *param)
{
	t_env *env;

	env = (t_env *)param;
	ft_putstr("KEYCODE ");
	ft_putnbr(keycode);
	ft_putendl("");
	if (keycode == 53 || keycode == 12)
	{
		mlx_destroy_window(env->mlx, env->display);
		ft_putendl("EXITING ...");
		exit(0);
	}
	if (keycode == 124)
	{
		mlx_clear_window(env->mlx, env->display);
		env->cursr_x += 10;
		render(env);
	}
	if (keycode == 123)
	{
		mlx_clear_window(env->mlx, env->display);
		env->cursr_x -= 10;
		render(env);
	}
	if (keycode == 125)
	{
		mlx_clear_window(env->mlx, env->display);
		env->cursr_y += 10;
		render(env);
	}
	if (keycode == 126)
	{
		mlx_clear_window(env->mlx, env->display);
		env->cursr_y -=10;
		render(env);
	}
	return (0);
}
