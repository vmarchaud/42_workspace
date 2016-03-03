/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:16:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 15:45:48 by vmarchau         ###   ########.fr       */
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
		del_alias(gbl->aliases, args[1]);
}

void	builtin_alias(t_global *gbl, int size, char **args)
{
	if (size != 3)
		return (ft_putendl_fd("usage error : alias <key> <value>", 2));
	if (!args[1] || !args[2])
		return (ft_putendl_fd("syntax error : alias <key> <value>", 2));
	put_alias(gbl, args[1], args[2]);
}
