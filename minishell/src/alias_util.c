/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:05:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/16 15:18:37 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_alias	*find_alias(t_global *gbl, char *name)
{
	t_alias *tmp;

	tmp = gbl->aliases;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_alias	*put_alias(t_global *gbl, char *key, char *value)
{
	t_alias	*tmp;

	if ((tmp = find_alias(gbl, key)) != NULL)
		tmp->value = value;
	else
		gbl->aliases = add_alias(gbl->aliases, new_alias(key, value));
	return (gbl->aliases);
}
