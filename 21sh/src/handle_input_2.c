/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:09:37 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/30 15:31:32 by vmarchau         ###   ########.fr       */
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

	if (IS_CLIP_A(input) && gbl->cursor->x != ft_strlen(line))
		gbl->clipboard = ft_strdup(line + gbl->cursor->x);
	else if (IS_CLIP_X(input) && gbl->cursor->x != ft_strlen(line))
	{
		gbl->clipboard = ft_strdup(line + gbl->cursor->x);
		line[gbl->cursor->x] = 0;
		ft_putstr(tgetstr("ce", NULL));
	}
	else if (IS_CLIP_P(input) && gbl->clipboard != NULL)
	{
		line = handle_rewriting(gbl, gbl->clipboard, line);
		i = ft_strlen(gbl->clipboard) - 1;
		while (i > 0)
		{
			ft_putstr(tgetstr("nd", NULL));
			gbl->cursor->x++;
			i--;
		}
	}
	return (line);
}
