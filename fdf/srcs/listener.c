/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:48:05 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 14:57:48 by vmarchau         ###   ########.fr       */
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
	if (keycode == 53)
	{
		mlx_destroy_window(env->mlx, env->display);
		ft_putendl("EXITING ...");
		exit(0);
	}
	return (0);
}
