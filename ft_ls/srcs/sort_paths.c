/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:46:56 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/22 15:34:19 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	ft_swap_path(t_path	*cur, t_path *next)
{
	void			*swap;
	struct s_path	*swap_path;
	struct s_filew	*swap_files;
	struct stat		*swap_stat;

	swap = cur->name;
	cur->name = next->name;
	next->name = swap;
	swap_path = cur->paths;
	cur->paths = next->paths;
	next->paths = swap_path;
	swap_files = cur->files;
	cur->files = next->files;
	next->files = swap_files;
	swap_stat = cur->stat;
	cur->stat = next->stat;
	next->stat = swap_stat;
}

void				sort_paths_by_alpha(t_path *path)
{
	t_path		*curr;
	t_path		*prev;

	curr = path->paths;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->name, curr->next->name) > 0)
		{
			ft_swap_path(curr, curr->next);
			curr = path->paths;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}

void				sort_paths_by_time(t_path *path)
{
	t_path		*curr;
	t_path		*prev;

	curr = path->paths;
	while (curr->next != NULL)
	{
		if (curr->stat->st_mtime < curr->next->stat->st_mtime)
		{
			ft_swap_path(curr, curr->next);
			curr = path->paths;
			prev = NULL;
		}
		prev = curr;
		curr = curr->next;
	}
}


void		sort_paths_reverse(t_path *list)
{
	t_path		*tmp;
	t_path		*first;
	t_path		*new;

	tmp = list->paths;
	first = NULL;
	while (tmp)
	{
		new = first;
		first = tmp;
		tmp = tmp->next;
		first->next = new;
	}
	list->paths = first;
}
