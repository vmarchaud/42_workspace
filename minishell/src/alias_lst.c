/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:37:32 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 14:18:21 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_alias	*new_alias(char *key, char *value)
{
	t_alias	*new;

	if ((new = malloc(sizeof(t_env))) == NULL)
		return (NULL);
	new->next = NULL;
	new->key = key;
	new->value = value;
	return (new);
}


t_alias	*add_alias(t_alias *head, t_alias *entry)
{
	t_alias	*tmp;

	if (head == NULL)
		head= entry;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = entry;
	}
	return (head);
}

void	clear_alias(t_alias *env)
{
	env->next = NULL;
	free(env->value);
	free(env->key);
	free(env);
	env = NULL;
}

t_alias	*del_alias(t_alias *head, char *key)
{
	t_alias	*tmp;
	t_alias	*prev;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (!prev)
			{
				head = head->next;
				clear_alias(tmp);
			}
			else
			{
				prev->next = tmp->next;
				clear_alias(tmp);
			}
			return (head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}
