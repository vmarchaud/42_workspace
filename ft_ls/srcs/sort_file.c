/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:46:56 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/21 16:08:57 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_filew		*find_prev(t_filew **head, char *name)
{
	t_filew *tmp;

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

static void			swap(t_filew *f1, t_filew *f2, t_filew *f3)
{
	f1->next = f3;
	f2->next = f3->next;
	f3->next = f2;
}

void				sort_file_by_alpha(t_path *path)
{
	t_filew		*curr;
	t_filew		*prev;

	curr = path->files;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->name, curr->next->name) > 0)
		{
			prev = find_prev(&path->files, curr->name);
			swap(prev, curr, curr->next);
			curr = path->files;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}

void				sort_file_reverse(t_path *path)
{
	t_filew		*tmp;	
	t_filew		*first;
	t_filew		*new;

	tmp = path->files;
	first = NULL;
	while (tmp)
	{
		new = first;
		first= tmp;
		tmp = tmp->next;
		first->next = new;
	}
	path->files = first;
}
























