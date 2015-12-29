/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:13:08 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 15:14:22 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render(t_env *env)
{
	t_point	*tmp;

	tmp = env->first->next;
	while (tmp != NULL)
	{
		mlx_pixel_put(env->mlx, env->display, tmp->x, tmp->y, 16777215);
		tmp = tmp->next;
	}
}
