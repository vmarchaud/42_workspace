/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:37:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/08 16:20:02 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		compute_dir(t_env *env, t_path *path)
{
	struct dirent	*tmp;
	DIR				*dir;
	char			*name;

	if (S_ISLNK(path->stat->st_mode))
		name = get_real_path(path->name);
	else
		name = path->name;
	if ((dir = opendir(name)) == NULL)
	{
		perror(path->name);
		return ;
	}
	path->files = NULL;
	while ((tmp = readdir(dir)) != NULL)
	{
		if (env->recursive)
		{
			if (tmp->d_type == DT_DIR && !is_hidden(env, tmp->d_name))
				ft_addpath_path(path, ft_strjoins(name, "/", tmp->d_name));
		}
		ft_addfile(path, tmp);
	}
	explore_dir(env, path);
	closedir(dir);
}

void		explore_dir(t_env *env, t_path *path)
{
	t_path *tmp;

	if (path->files)
		path->files = sort_file_by_alpha(path->files);
	if (env->sort_time == TRUE)
		sort_file_by_time(path->files);
	if (env->reverse == TRUE)
		path->files = sort_file_reverse(path->files);
	if (env->format_out)
		show_format_path(env, path);
	else
		show_path(env, path);
	tmp = path->paths;
	if (tmp != NULL)
		sort_paths_by_alpha(path);
	if (tmp != NULL && env->sort_time == TRUE)
		sort_paths_by_time(path);
	if (tmp != NULL && env->reverse == TRUE)
		path->paths = sort_paths_reverse(path->paths);
	tmp = path->paths;
	while (tmp != NULL)
	{
		compute_dir(env, tmp);
		tmp = tmp->next;
	}
}
