/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:16:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/16 15:20:06 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unalias(t_global *gbl, int size, char **args)
{
	t_alias	*entry;

	if (size != 2)
		return (ft_putendl_fd("usage error : unalias <key>", 2));
	if (!args[1])
		return (ft_putendl_fd("syntax error : unalias <key>", 2));
	entry = find_alias(gbl, args[1]);
	if (entry == NULL)
		return (ft_putendl_fd("error : alias not found", 2));
	else
		gbl->aliases = del_alias(gbl->aliases, args[1]);
}

void	builtin_alias(t_global *gbl, int size, char **args)
{
	if (size != 3)
		return (ft_putendl_fd("usage error : alias <key> <value>", 2));
	if (!args[1] || !args[2])
		return (ft_putendl_fd("syntax error : alias <key> <value>", 2));
	gbl->aliases = put_alias(gbl, ft_strdup(args[1]), ft_strdup(args[2]));
}

void	builtin_aliaslist(t_global *gbl, int size, char **args)
{
	t_alias	*tmp;

	(void)size;
	(void)args;
	tmp = gbl->aliases;
	while (tmp)
	{
		write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}
