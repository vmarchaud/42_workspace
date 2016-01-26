/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:37:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/26 14:51:50 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		compute_dir(t_env *env, t_path *path)
{
	struct dirent	*tmp;
	DIR				*dir;

	if ((dir = opendir(path->name)) == NULL)
	{
		perror(path->name);
		return ;
	}
	path->files = NULL;
	while ((tmp = readdir(dir)) != NULL)
	{
		if (env->recursive && tmp->d_type == DT_DIR &&
				!is_hidden(env, tmp->d_name))
			ft_addpath_path(path, ft_strjoins(path->name, "/", tmp->d_name));
		ft_addfile(path, tmp);
	}
	closedir(dir);
	explore_dir(env, path);
}

void		show_content(t_env *env, t_path *path)
{
	t_filew		*tmp;
	short		i;

	i = 0;
	tmp = path->files;
	if (ft_strcmp(path->name, ".") != 0 && ft_strcmp(path->name, "..") != 0)
		ft_putendl(path->name);
	while (tmp != NULL)
	{
		if (is_hidden(env, tmp->name) && !env->show_dot)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr(tmp->name);
		if (i > 3 && !(i = 0))
			ft_putchar('\n');
		else
			ft_putstr("\t");
		tmp = tmp->next;
		i++;
	}
	ft_putstr("\n\n");
}

void		show_format_content(t_env *env, t_path *path)
{
	t_filew		*tmp;
	char		*buff;

	tmp = path->files;
	buff = NULL;
	while (tmp != NULL)
	{
		if (!env->show_dot && is_hidden(env, tmp->name))
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr(buff = get_file_type(tmp->stat->st_mode));
		ft_putstr(buff = get_file_rights(tmp->stat->st_mode));
		ft_putstr(" ");
		ft_putstr(buff = ft_itoa(tmp->stat->st_nlink));
		ft_putstr("\t");
		ft_putstr(buff = get_file_owner(tmp->stat->st_uid));
		ft_putstr("\t");
		ft_putstr(buff = get_file_group(tmp->stat->st_gid));
		ft_putstr("\t");
		ft_putnbr(tmp->stat->st_size);
		ft_putstr("\t");
		ft_putstr(buff = get_file_time(tmp->stat->st_mtime));
		ft_putstr(" ");
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

void		explore_dir(t_env *env, t_path *path)
{
	t_path *tmp;

	if (env->sort_time == FALSE)
		sort_file_by_alpha(path);
	if (env->sort_time == TRUE)
		sort_file_by_time(path);
	if (env->reverse == TRUE)
		sort_file_reverse(path);
	if (env->format_out)
		show_format_content(env, path);
	else
		show_content(env, path);
	tmp = path->paths;
	if (tmp != NULL && env->sort_time == FALSE)
		sort_paths_by_alpha(path);
	if (tmp != NULL && env->sort_time == TRUE)
		sort_paths_by_time(path);
	if (tmp != NULL && env->reverse == TRUE)
		sort_paths_reverse(path);
	tmp = path->paths;
	while (tmp != NULL)
	{
		compute_dir(env, tmp);
		tmp = tmp->next;
	}
}
