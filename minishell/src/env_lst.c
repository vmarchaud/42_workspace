/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:37:32 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 13:14:55 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_entry(char *key, char *value)
{
	t_env	*new;

	if ((new = malloc(sizeof(t_env))) == NULL)
		return (NULL);
	new->next = NULL;
	new->key = key;
	new->value = value;
	new->old_value = NULL;
	return (new);
}


t_env	*add_env_entry(t_env *env, t_env *entry)
{
	if (!env)
		env = entry;
	else
	{
		tmp = env;
		while (tmp->next)
			tmp = tmp-next;
		tmp->next = entry;
	}
	return (env);
}

void	clear_entry(t_env *env)
{
	env->next = NULL;
	free(env->value);
	free(env->key);
	if (env->old_value != NULL)
		free(env->old_value);
	free(env);
	env = NULL;
}

t_env	*del_env_entry(t_env *head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (!prev)
				clear_elem(head);
			else
			{
				prev->next = tmp->next;
				clear_elem(tmp);
			}
			return (head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}
