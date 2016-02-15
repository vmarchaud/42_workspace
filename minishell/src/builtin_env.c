/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:16:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 13:21:01 by vmarchau         ###   ########.fr       */
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
