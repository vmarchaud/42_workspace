
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 14:44:27 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/22 14:46:56 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		*lst_newpt(int x, int y, int h)
{
	t_point		*tmp;

	if ((tmp = (t_point*)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	tmp->x = x;
	tmp->y = y - h;
	tmp->next = NULL;
	return (tmp);
}

void	debug_point(t_env *env)
{
	t_point *tmp;

	tmp = env->first;
	while (tmp != NULL)
	{
		ft_putstr("X: ");
		ft_putnbr(tmp->x);
		ft_putstr(" & Y: ");
		ft_putnbr(tmp->y);
		ft_putendl("");
		tmp = tmp->next;
	}
}
