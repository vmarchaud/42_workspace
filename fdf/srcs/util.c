
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

t_point		*lst_newpt(int x, int y, int h, int index)
{
	t_point		*tmp;

	if ((tmp = (t_point*)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	tmp->x = x;
	tmp->y = y - h;
	tmp->index = index;
	tmp->next = NULL;
	return (tmp);
}

void	debug_point(t_point *point)
{
    ft_putstr("X: ");
    ft_putnbr(point->x);
    ft_putstr(" & Y: ");
    ft_putnbr(point->y);
    ft_putstr(" with index :");
    ft_putnbr(point->index);
    ft_putendl("");
    
}

void	debug_points(t_env *env)
{
	t_point *tmp;

	tmp = env->first->next;
	while (tmp != NULL)
	{
		if (tmp->index == 0)
			ft_putstr("\n NEW LINE \n");
		ft_putstr("X: ");
		ft_putnbr(tmp->x);
		ft_putstr(" & Y: ");
		ft_putnbr(tmp->y);
		ft_putstr(" width index :");
		ft_putnbr(tmp->index);
		ft_putendl("");
		if (tmp->index == env->size_x)
			ft_putstr("\n END LINE \n");
		tmp = tmp->next;
	}
}
