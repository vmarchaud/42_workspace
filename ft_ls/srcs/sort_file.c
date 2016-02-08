/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:46:56 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/08 15:16:46 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			swap_files(t_filew *cur, t_filew *next)
{
	void		*swap;
	__uint8_t	*tmp;
	struct stat *tmpp;

	swap = cur->name;
	cur->name = next->name;
	next->name = swap;
	tmp = cur->type;
	cur->type = next->type;
	next->type = tmp;
	tmpp = cur->stat;
	cur->stat = next->stat;
	next->stat = tmpp;
	swap = cur->path;
	cur->path = next->path;
	next->path = swap;
}

void				sort_file_by_alpha(t_filew *lst)
{
	t_filew	*tmp;
	int		flag;

	flag = 1;
	if (!lst || !lst->next)
		return ;
	while (flag)
	{
		tmp = lst;
		flag = 0;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				swap_files(tmp, tmp->next);
				flag = 1;
			}
			tmp = tmp->next;
		}
	}
}

void				sort_file_by_time(t_filew *lst)
{
	t_filew *tmp;
	int		flag;

	flag = 1;
	if (!lst || !lst->next)
		return ;
	while (flag)
	{
		tmp = lst;
		flag = 0;
		while (tmp->next)
		{
			if (tmp->stat->st_mtime < tmp->next->stat->st_mtime)
			{
				swap_files(tmp, tmp->next);
				flag = 1;
			}
			tmp = tmp->next;
		}
	}
}

t_filew				*sort_file_reverse(t_filew *file)
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
	return (list);
}
