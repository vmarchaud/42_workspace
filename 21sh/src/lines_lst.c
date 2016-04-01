/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 13:03:45 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 14:04:42 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line		*new_line(t_global *gbl)
{
	t_line	*new;

	if ((new = malloc(sizeof(t_line))) == NULL)
		return (NULL);
	new->content = ft_strnew(1);
	new->index = find_available_index(gbl);
	new->size = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_line		*add_line(t_global *gbl)
{
	t_line	*new;
	t_line	*tmp;

	new = new_line(gbl);
	if (new->index == 1)
		new->prev = gbl->lines;
	else
	{
		tmp = gbl->lines;
		while (tmp->index != new->index - 1)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (new);
}

void		delete_line(t_line *line)
{
	free(line->content);
	free(line);
}

size_t		find_available_index(t_global *gbl)
{
	t_line	*tmp;

	tmp = gbl->lines;
	if (tmp == NULL)
		return (0);
	else
		while (tmp->next)
			tmp = tmp->next;
	return (tmp->index + 1);
}
