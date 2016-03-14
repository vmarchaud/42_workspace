/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:05:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/14 14:44:42 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assmbl_env(char *key, char *value)
{
	char	*ret;
	char	*del;

	ret = ft_strjoin(key, "=");
	del = ret;
	ret = ft_strjoin(ret, value);
	free(del);
	return (ret);
}

t_env	*deassmbl_env(char *entry)
{
	t_env	*env;
	char	**tab;

	tab = ft_strsplit(entry, '=');
	env = new_entry(tab[0], tab[1]);
	return (env);
}

t_env	*find_entry(t_global *gbl, char *name)
{
	t_env *tmp;

	tmp = gbl->env;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*put_entry(t_global *gbl, char *key, char *value)
{
	t_env	*tmp;

	if ((tmp = find_entry(gbl, key)) != NULL)
	{
		tmp->old_value = tmp->value;
		tmp->value = value;
	}
	else
		add_env_entry(gbl->env, new_entry(key, value));
	return (gbl->env);
}
