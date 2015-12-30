/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 14:40:35 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/30 16:06:07 by vmarchau         ###   ########.fr       */
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
			if (ft_atoi(tab[i]) < 0)
				return (-1);
			tmp->next = lst_newpt(i * 10, y * 10, ft_atoi(tab[i]) * 10);
			tmp = tmp->next;
			i++;
		}
		env->line_len = i;
		free_ptr(tab, line);
		y++;
	}
	return (1);
}
