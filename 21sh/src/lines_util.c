/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 13:33:10 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 14:06:26 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compact_lines(t_global *gbl)
{
	char	*str;
	char	*del;
	t_line 	*tmp;

	tmp = gbl->lines;
	str = ft_strnew(1);
	while (tmp->prev)
		tmp = tmp->prev;
	if (tmp->size == 0)
		return (ft_strnew(1));
	else
		while (tmp)
		{
			del = str;
			str = ft_strjoin(str, tmp->content);
			free(del);
			tmp = tmp->next;
		}
	return (str);
}

t_line	*reset_lines(t_global *gbl)
{
	t_line	*tmp;
	t_line	*next;

	tmp = gbl->lines;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		next = tmp->next;
		delete_line(tmp);
		tmp = next;
	}
	gbl->lines = add_line(gbl);
	return (gbl->lines);
}
