/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:59 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/08 13:01:13 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path		*ft_newpath(char *name)
{
	t_path *path;

	if ((path = (t_path*)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	if ((path->stat = (struct stat*)malloc(sizeof(struct stat))) == NULL)
		return (NULL);
	path->name = name;
	path->files = NULL;
	path->paths = NULL;
	path->next = NULL;
	return (path);
}

t_filew		*ft_newfile(struct dirent *dirent)
{
	t_filew	*f;

	if ((f = (t_filew*)malloc(sizeof(t_filew))) == NULL)
		return (NULL);
	f->name = ft_strdup(dirent->d_name);
	f->next = NULL;
	if ((f->stat = (struct stat*)malloc(sizeof(struct stat))) == NULL)
		return (NULL);
	f->path = NULL;
	return (f);
}

void		ft_addfile(t_path *path, struct dirent *dirent)
{
	t_filew *file;
	t_filew *tmp;
	char	*del;

	file = ft_newfile(dirent);
	lstat((del = ft_strjoins(path->name, "/", dirent->d_name)), file->stat);
	free(del);
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

void		ft_addpath_env(t_env *env, char *name)
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

void		ft_addpath_path(t_path *path, char *name)
{
	t_path *newpath;
	t_path *tmp;

	newpath = ft_newpath(name);
	stat(name, newpath->stat);
	if (path->paths == NULL)
		path->paths = newpath;
	else
	{
		tmp = path->paths;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newpath;
	}
}
