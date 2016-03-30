/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:02:24 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/30 13:27:21 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		reset_cursor(t_global *gbl)
{
	gbl->cursor->x = 0;
	gbl->cursor->y = 0;
	ft_putstr(tgetstr("sc", NULL));
}

void		goto_start(t_global *gbl)
{
	size_t	x;
	size_t	y;

	x = gbl->cursor->x;
	y = gbl->cursor->y;
	while (x > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		x--;
	}
	while (y > 0)
	{
		ft_putstr(tgetstr("up", NULL));
		y--;
	}
}

void		goto_end(t_global *gbl, char *line)
{
	while (gbl->cursor->x != ft_strlen(line))
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->cursor->x++;
	}
}

void		next_word(t_global *gbl, char	*line)
{
	size_t	i;

	i = gbl->cursor->x + 1;
	while (line[i])
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->cursor->x++;
		if (line[i] != ' ' && line[i - 1] == ' ')
			break ;
		else
			++i;
	}
}

void		prev_word(t_global *gbl, char	*line)
{
	size_t	i;

	i = gbl->cursor->x - 1;
	while (i > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->cursor->x--;
		if (line[i] != ' ' && line[i - 1] == ' ')
			break ;
		else
			i--;
	}
	if (i == 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->cursor->x--;
	}
}
