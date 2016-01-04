/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 14:40:35 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/04 15:54:04 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	free_ptr(char **tab, char *line)
{
	free(tab);
	free(line);
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
			tmp->next = lst_newpt((i - y) * env->zoom, (y + i) * env->zoom,
					ft_atoi(tab[i]) * 5, i);
			tmp = tmp->next;
			i++;
		}
		env->size_x = i;
		free_ptr(tab, line);
		y++;
	}
	env->size_y = y;
	return (1);
}
