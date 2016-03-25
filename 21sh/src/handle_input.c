/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:01:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/25 14:36:09 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_arrow(t_global *gbl, char *input, char *line) {
	if (ISARROW_LEFT(input) && gbl->cursor->x != 0)
	{
		ft_putstr(tgetstr("le", NULL));
		gbl->cursor->x--;
	}
	else if (ISARROW_RIGHT(input) && gbl->cursor->x != ft_strlen(line))
	{
		ft_putstr(tgetstr("nd", NULL));
		gbl->cursor->x++;
	}
	else if ((ISARROW_UP(input) || ISARROW_DOWN(input)) && gbl->history)
	{
		if ((ISARROW_UP(input) && gbl->history->next == NULL) ||
			(ISARROW_DOWN(input) && gbl->history->prev == NULL))
			return (line);
		ft_putstr(tgetstr("rc", NULL));
		ft_putstr(tgetstr("ce", NULL));
		if (ISARROW_UP(input))
			gbl->history = gbl->history->next;
		else
			gbl->history = gbl->history->prev;
		line = ft_strdup(gbl->history->cmd);
		ft_putstr(line);
		gbl->cursor->x = ft_strlen(line);
	}
  return (line);
}

char	*handle_delete(t_global *gbl, char *input, char *line)
{
	size_t		i;

	(void)input;
	i = ft_strlen(line);
	if (gbl->cursor->x == i && i != 0)
	{
		line[i - 1] = 0;
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("ce", NULL));
		gbl->cursor->x--;
		return (line);
	}
	line = ft_str_leftpad(line, gbl->cursor->x - 1, 1);
	ft_putstr(tgetstr("le", NULL));
	ft_putstr(tgetstr("sc", NULL));
	ft_putstr(tgetstr("ce", NULL));
	ft_putstr(line + gbl->cursor->x - 1);
	ft_putstr(tgetstr("rc", NULL));
	gbl->cursor->x--;
	return (line);
}

char	*handle_input(t_global *gbl, char *input, char *line)
{
	char	*tmp;

	(void)gbl;
	if (ISARROW(input))
 		line = handle_arrow(gbl, input, line);
	else if (input[0] == 127 && gbl->cursor->x > 0)
		line = handle_delete(gbl, input, line);
	else if (ft_isprint(input[0]) || input[0] == '\n' || input[0] == '\t')
	{
		tmp = line;
		line = ft_strjoin(line, input);
		free(tmp);
		ft_putstr(input);
		gbl->cursor->x++;
	}
	return (line);
}
