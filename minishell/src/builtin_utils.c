/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:25:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 15:09:29 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd		*new_cmd(char *name, builtin_cmd *func)
{
	t_cmd	*new;

	if ((new = malloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	new->name = name;
	new->func = func;
	new->next = NULL;
	return (new);
}

t_cmd		*register_cmd(t_global *gbl, char *name, builtin_cmd *func)
{
	t_cmd	*tmp;
	t_cmd	*new;
	
	new = new_cmd(name, func);
	tmp = gbl->cmds;
	if (!gbl->cmds)
		gbl->cmds = new;
	else
	{
		tmp = gbl->cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (gbl->cmds);
}

t_cmd		*find_cmd(t_global *gbl, char *name)
{
	t_cmd *tmp;

	tmp = gbl->cmds;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
