/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:16:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/16 15:54:15 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_env(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		write(2, "AA", 2);
		write(1, tmp->key, ft_strlen(tmp->key));
		write(2, "BB", 2);
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	builtin_env(t_global *gbl, int size, char **args)
{
	char	*tmp;

	tmp = NULL;
	if (size == 1)
		show_env(gbl->env);
	else if (size >= 3 && ft_strcmp(args[1], "-i") == 0)
		execute_cmd(gbl, size - 2, &args[2], &tmp);
}

void	builtin_unsetenv(t_global *gbl, int size, char **args)
{
	t_env	*entry;

	if (size != 2)
		return (ft_putendl_fd("usage error : unsetenv <key>", 2));
	if (!args[1] || ft_strchr(args[1], '='))
		return (ft_putendl_fd("syntax error : unsetenv <key>", 2));
	entry = find_entry(gbl, args[1]);
	if (entry == NULL)
		return (ft_putendl_fd("error : entry not found", 2));
	gbl->env = del_env_entry(gbl->env, args[1]);
	gbl->env_size--;
	update_tabenv(gbl);
}

void	builtin_setenv(t_global *gbl, int size, char **args)
{
	if (size != 3)
		return (ft_putendl_fd("usage error : setenv <key> <value>", 2));
	if (!args[1] || ft_strchr(args[1], '=') ||
			!args[2] || ft_strchr(args[2], '='))
		return (ft_putendl_fd("syntax error : setenv <key> <value>", 2));
	gbl->env = put_entry(gbl, args[1], args[2]);
	update_tabenv(gbl);
}
