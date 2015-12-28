/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 14:40:35 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/22 15:39:13 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	tmp = lst_newpt(0, 0, 0);
	env->first = tmp;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		i = 0;
		while (tab[i] != NULL)
		{
			tmp->next = lst_newpt(i, y, ft_atoi(tab[i]));
			tmp = tmp->next;
		}
		free_ptr(tab, line);
		j++;
	}
	return (1);
}
