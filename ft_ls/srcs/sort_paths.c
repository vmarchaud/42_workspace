/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:46:56 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/20 14:37:22 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_path		*find_prev(t_path **head, char *name)
{
	t_path *tmp;

	tmp = *head;
	if (ft_strcmp((*head)->name, name) == 0)
		return (*head);
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		swap(t_path *f1, t_path *f2, t_path *f3)
{
	f1->next = f3;
	f2->next = f3->next;
	f3->next = f2;
}

void		sort_paths_by_alpha(t_path *path)
{
	t_path		*curr;
	t_path		*prev;

	curr = path->paths;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->name, curr->next->name) > 0)
		{
			prev = find_prev(&path->paths, curr->name);
			swap(prev, curr, curr->next);
			curr = path->paths;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}

void		sort_paths_reverse(t_path *path)
{
	t_path		*tmp;	
	t_path		*first;
	t_path		*new;

	tmp = path->paths;
	first = NULL;
	while (tmp)
	{
		new = first;
		first= tmp;
		tmp = tmp->next;
		first->next = new;
	}
	path->paths = first;
}
