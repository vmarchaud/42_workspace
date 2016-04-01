/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:02:24 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 15:00:57 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		reset_cursor(t_global *gbl)
{
	gbl->term->x = 0;
	gbl->term->y = 0;
	ft_putstr(tgetstr("sc", NULL));
}

void		goto_start(t_global *gbl)
{
	while (gbl->term->x > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->term->x--;
	}
}

void		goto_end(t_global *gbl, char *line)
{

	while (gbl->term->x != ft_strlen(line))
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->term->x++;
	}
}

void		next_word(t_global *gbl, char	*line)
{
	size_t	i;

	i = gbl->term->x + 1;
	while (line[i])
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->term->x++;
		if (line[i] != ' ' && line[i - 1] == ' ')
			break ;
		else
			++i;
	}
}

void		prev_word(t_global *gbl, char	*line)
{
	size_t	i;

	if (gbl->term->x == 0)
		return ;
	i = gbl->term->x - 1;
	while (i > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->term->x--;
		if (line[i] != ' ' && line[i - 1] == ' ')
			break ;
		else
			i--;
	}
	if (i == 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->term->x--;
	}
}
