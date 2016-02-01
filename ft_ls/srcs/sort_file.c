/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:46:56 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/29 15:18:56 by vmarchau         ###   ########.fr       */
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

void				sort_file_by_alpha(t_filew *file)
{
	t_filew		*curr;
	t_filew		*prev;

	curr = file;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->name, curr->next->name) > 0)
		{
			prev = find_prev(&file, curr->name);
			swap(prev, curr, curr->next);
			curr = file;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}

void				sort_file_by_time(t_filew *file)
{
	t_filew		*curr;
	t_filew		*prev;

	curr = file;
	while (curr->next != NULL)
	{
		if (curr->stat->st_mtime < curr->next->stat->st_mtime)
		{
			prev = find_prev(&file, curr->name);
			swap(prev, curr, curr->next);
			curr = file;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}

void				sort_file_reverse(t_filew *file)
{
	t_filew *tmp1;
	t_filew *tmp2;
	t_filew *list;

	list = file;
	if (list != NULL)
	{
		tmp1 = list->next;
		list->next = NULL;
		while (tmp1 != NULL)
		{
			tmp2 = tmp1->next;
			tmp1->next = list;
			list = tmp1;
			tmp1 = tmp2;
		}
	}
	file = list;
}
