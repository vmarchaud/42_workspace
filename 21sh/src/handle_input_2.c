/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:09:37 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 15:11:45 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_home_end(t_global *gbl, char *input, char *line)
{
	if (IS_HOME(input))
		goto_start(gbl);
	else if (IS_END(input))
		goto_end(gbl, line);
	return (line);
}

char	*handle_clipboard(t_global *gbl, char *input, char *line)
{
	int	i;

	if (IS_CLIP_A(input) && gbl->term->x != ft_strlen(line))
		gbl->clipboard = ft_strdup(line + gbl->term->x);
	else if (IS_CLIP_X(input) && gbl->term->x != ft_strlen(line))
	{
		gbl->clipboard = ft_strdup(line + gbl->term->x);
		line[gbl->term->x] = 0;
		ft_putstr(tgetstr("cd", NULL));
	}
	else if (IS_CLIP_P(input) && gbl->clipboard != NULL)
	{
		line = handle_rewriting(gbl, gbl->clipboard, line);
		i = ft_strlen(gbl->clipboard) - 1;
		while (i > 0)
		{
			ft_putstr(tgetstr("nd", NULL));
			gbl->term->x++;
			i--;
		}
	}
	return (line);
}

char	*handle_enter(t_global *gbl, char *input, char *line)
{
	char	*del;

	if (line[ft_strlen(line) - 1] == 92)
	{
		del = line;
		line = ft_strjoin(line, input);
		free(del);
		ft_putstr(input);
		gbl->term->x = 0;
		gbl->term->y++;
		gbl->lines = add_line(gbl);
	}
	else
	{
		ft_putstr(input);
		gbl->submit_line = TRUE;
	}
	return (line);
}
