/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 14:15:15 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/03 14:35:09 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_files(t_filew *file)
{
	t_filew *tmp;
	t_filew	*next;

	tmp = file;
	file = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->stat);
		free(tmp->type);
		free(tmp);
		tmp = next;
	}
}

void	free_paths(t_path *path)
{
	t_path	*tmp;
	t_path *next;
	
	tmp = path;
	path = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->paths)
			free_paths(tmp->paths);
		free(tmp->name);
		free(tmp->stat);
		free(tmp);
		tmp = next;
	}
}
