/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:59 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/19 13:07:10 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path		*ft_newpath(char *name)
{
	t_path *path;

	if ((path = (t_path*)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	path->name = name;
	path->files = NULL;
	path->next = NULL;
	return (path);
}

t_filew		*ft_newfile(struct dirent *dirent)
{
	t_filew	*f;

	if ((f = (t_filew*)malloc(sizeof(t_filew))) == NULL)
		return (NULL);
	f->name = ft_strdup(dirent->d_name);
	if ((f->type = (__uint8_t*)malloc(sizeof(__uint8_t))) == NULL)
		return (NULL);
	ft_memcpy(f->type, &dirent->d_type, sizeof(dirent->d_type));
	f->next = NULL;
	return (f);
}

void		ft_addfile_to_lst(t_filew *first, t_filew *new)
{
	t_filew *tmp;

	if (!first)
		first = new;
	else
	{
		tmp = first;
		while (tmp != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		ft_addfile(t_path *path, struct dirent *dirent)
{
	t_filew *file;
	t_filew *tmp;

	file = ft_newfile(dirent);
	if (path->files == NULL)
		path->files = file;
	else
	{
		tmp = path->files;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = file;
	}
}

void		ft_addpath(t_env *env, char *name)
{
	t_path *path;
	t_path *tmp;

	path = ft_newpath(name);
	if (env->paths == NULL)
		env->paths = path;
	else
	{
		tmp = env->paths;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = path;
	}
}
