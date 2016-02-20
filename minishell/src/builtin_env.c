/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:16:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/20 14:54:35 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	show_env(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}


void	builtin_env(t_global *gbl, int size, char **args)
{
	(void)size;
	(void)args;
	show_env(gbl->env);
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
	else
		del_env_entry(gbl->env, args[1]);
	gbl->env_size--;
	update_tabenv(gbl);
}

void	builtin_setenv(t_global *gbl, int size, char **args)
{
	t_env	*entry;

	if (size != 3)
		return (ft_putendl_fd("usage error : setenv <key> <value>", 2));
	if (!args[1] || ft_strchr(args[1], '=') ||
			!args[2] || ft_strchr(args[2], '='))
		return (ft_putendl_fd("syntax error : setenv <key> <value>", 2));

	entry = find_entry(gbl, args[1]);
	if (entry == NULL)
		add_env_entry(gbl->env, new_entry(args[1], args[2]));
	else {
		entry->old_value = entry->value;
		entry->value = args[2];
	}
	if (entry == NULL)
		gbl->env_size++;
	update_tabenv(gbl);
}
