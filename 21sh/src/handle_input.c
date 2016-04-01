/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:01:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 15:08:17 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_arrow(t_global *gbl, char *input, char *line)
{
	if (ISARROW_LEFT(input) && gbl->term->x != 0)
		ft_putstr(tgetstr("le", NULL + (gbl->term->x-- & 0)));
	else if (ISARROW_RIGHT(input) && gbl->term->x != ft_strlen(line))
		ft_putstr(tgetstr("nd", NULL + (gbl->term->x++ & 0)));
	else if ((ISARROW_UP(input) || ISARROW_DOWN(input)) && gbl->history)
	{
		if ((ISARROW_UP(input) && gbl->history->next == NULL) ||
			(ISARROW_DOWN(input) && gbl->history->prev == NULL))
			return (line);
		ft_putstr(tgetstr("rc", NULL));
		ft_putstr(tgetstr("cd", NULL));
		if (ISARROW_UP(input))
			gbl->history = gbl->history->next;
		else
			gbl->history = gbl->history->prev;
		line = ft_strdup(gbl->history->cmd);
		ft_putstr(line);
		gbl->term->x = ft_strlen(line);
	}
	return (line);
}

char	*handle_left_delete(t_global *gbl, char *input, char *line)
{
	size_t		i;

	(void)input;
	i = ft_strlen(line);
	if (gbl->term->x == i && i != 0)
	{
		line[i - 1] = 0;
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("ce", NULL));
		gbl->term->x--;
		return (line);
	}
	line = ft_str_leftpad(line, gbl->term->x - 1, 1);
	ft_putstr(tgetstr("le", NULL));
	ft_putstr(tgetstr("sc", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(line + gbl->term->x - 1);
	ft_putstr(tgetstr("rc", NULL));
	gbl->term->x--;
	return (line);
}

char	*handle_rewriting(t_global *gbl, char *input, char *line)
{
	char	*new;
	char	*del;
	char	*tmp;

	new = ft_strsub(line, 0, gbl->term->x);
	del = new;
	new = ft_strjoin(new, input);
	free(del);
	del = new;
	tmp = ft_strsub(line, gbl->term->x, ft_strlen(line) - gbl->term->x);
	new = ft_strjoin(new, tmp);
	free(tmp);
	free(del);
	ft_putstr(tgetstr("sc", NULL));
	ft_putstr(tgetstr("cd", NULL));
	ft_putstr(new + gbl->term->x);
	ft_putstr(tgetstr("rc", NULL));
	ft_putstr(tgetstr("nd", NULL));
	gbl->term->x++;
	free(line);
	return (new);
}

char 	*handle_ctrl_arrow(t_global *gbl, char *input, char *line)
{
	if (ISCTRLARROW_LEFT(input))
		prev_word(gbl, line);
	else if (ISCTRLARROW_RIGHT(input))
		next_word(gbl, line);
	return (line);
}

char	*handle_input(t_global *gbl, char *input, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	/*while (input[i])
	{
		ft_putchar(' ');
		ft_putnbr(input[i++]);
	}*/
	if (ISARROW(input))
		line = handle_arrow(gbl, input, line);
	else if (input[0] == 127 && gbl->term->x > 0)
		line = handle_left_delete(gbl, input, line);
	else if (ft_isprint(input[0]) && gbl->term->x != gbl->lines->size)
		line = handle_rewriting(gbl, input, line);
	else if (ISCTRLARROW(input))
		line = handle_ctrl_arrow(gbl, input, line);
	else if (IS_HOME_END(input))
		line = handle_home_end(gbl, input, line);
	else if (IS_CLIPBOARD(input))
		line = handle_clipboard(gbl, input, line);
	else if (input[0] == '\n')
		line = handle_enter(gbl, input, line);
	else if (ft_isprint(input[0]))
	{
		tmp = line;
		line = ft_strjoin(line, input);
		free(tmp);
		ft_putstr(input);
		gbl->term->x++;
	}
	return (line);
}
