/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:37:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 13:42:45 by vmarchau         ###   ########.fr       */
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
	if (!is_hidden(env, path->name) && !is_request_path(env, path->name))
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

void		show_format_file(t_env *env, t_filew *file)
{
	if (!env->show_dot && is_hidden(env, file->name))
		return ;
	print_file_type(file->stat->st_mode);
	print_file_rights(file->stat->st_mode);
	ft_putstr(" ");
	ft_putnbr(file->stat->st_nlink);
	ft_putstr("\t");
	print_file_owner(file->stat->st_uid);
	ft_putstr("\t");
	print_file_group(file->stat->st_gid);
	ft_putstr("\t");
	ft_putnbr(file->stat->st_size);
	ft_putstr("\t");
	print_file_time(file->stat->st_mtime);
	ft_putstr(" ");
	ft_putendl(file->name);
}

void		show_format_content(t_env *env, t_path *path)
{
	t_filew		*tmp;
	char		*buff;

	tmp = path->files;
	buff = NULL;
	if (!is_hidden(env, path->name) && is_request_path(env, path->name) == 0)
		ft_putendl(path->name);
	ft_putstr("total ");
	ft_putnbr(count_block_used(path));
	ft_putchar('\n');
	while (tmp != NULL)
	{
		show_format_file(env, tmp);
		tmp = tmp->next;
	}
	ft_putstr("\n\n");
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
