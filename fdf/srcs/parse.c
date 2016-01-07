/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 14:40:35 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/07 12:50:54 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ptr(char **tab, char *line)
{
	free(tab);
	free(line);
}

void	compute_position(t_env *env, int oldzoom, int olddiff)
{
	t_point *tmp;

	tmp = env->first->next;
	while (tmp != NULL)
	{
		tmp->y = (tmp->y + tmp->h) / oldzoom;
		tmp->h = tmp->h / olddiff;
		tmp->x /= oldzoom;
		tmp->h *= env->diff;
		tmp->y = tmp->y * env->zoom - tmp->h;
		tmp->x *= env->zoom;
		tmp = tmp->next;
	}
}

int		parse(int const fd, t_env *env)
{
	char	*line;
	int		i;
	t_point	*tmp;
	char	**tab;
	int		y;

	tmp = lst_newpt(0, 0, 0, 0);
	env->first = tmp;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		i = 0;
		while (tab[i] != NULL)
		{
			ft_putstr(tab[i]);
			ft_putstr(" ");
			tmp->next = lst_newpt((i - y), (y + i), ft_atoi(tab[i]), i);
			tmp = tmp->next;
			i++;
		}
		ft_putendl("");
		free_ptr(tab, line);
		y++;
	}
	env->size_x = i;
	env->size_y = y;
	return (1);
}
