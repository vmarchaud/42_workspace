/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:02:24 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/28 15:10:34 by vmarchau         ###   ########.fr       */
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

void		next_word(t_global *gbl, char	*line)
{
	size_t	i;

	i = 0;
	if ( gbl->cursor->x >= ft_strlen(line))
 		return ;
	while (line[i + 1])
		if (line[i] == ' ' && line[i + 1] != ' ')
			break ;
		else
			i++;
	while (i > 0)
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->cursor->x++;
		i--;
	}
}

void		prev_word(t_global *gbl, char	*line)
{
	size_t	i;

	if (gbl->cursor->x == 0)
		return ;
	i = gbl->cursor->x;
	while (i - 1> 0)
		if (line[i] != ' ' && line[i - 1] == ' ')
			break ;
		else
		{
			ft_putstr(tgetstr("le", NULL));
			gbl->cursor->x--;
			i--;
		}
}
