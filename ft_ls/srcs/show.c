/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 13:50:04 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/03 14:31:30 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		show_format_file(t_env *env, t_path *path, t_filew *file)
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
	if (S_ISCHR(file->stat->st_mode) || S_ISBLK(file->stat->st_mode))
		print_major_minor(file->stat->st_rdev);
	else
		ft_putnbr(file->stat->st_size);
	ft_putstr("\t");
	print_file_time(file->stat->st_mtime);
	ft_putstr(" ");
	if (!S_ISLNK(file->stat->st_mode))
		ft_putendl(file->name);
	else
		print_link(path, file);
}

void		show_format_path(t_env *env, t_path *path)
{
	t_filew		*tmp;

	tmp = path->files;
	if ((ft_strcmp(".", path->name) != 0 && ft_strcmp("..", path->name) != 0
			&& !is_request_path(env, path->name)) || env->show_path_name)
		ft_putendl(ft_strjoin(path->name, ":"));
	
	if (path->files != NULL)
	{
		ft_putstr("total ");
		ft_putnbr(count_block_used(env, path));
		ft_putchar('\n');
	}
	while (tmp != NULL)
	{
		show_format_file(env, path, tmp);
		tmp = tmp->next;
	}
	ft_putstr("\n");
	if (path->files)
		free_files(path->files);
}

void		show_file(t_env *env, t_path *path, t_filew *file)
{
	(void)path;
	if (!env->show_dot && is_hidden(env, file->name))
		return ;
	if (!S_ISLNK(file->stat->st_mode))
		ft_putendl(file->name);
}

void		show_path(t_env *env, t_path *path)
{
	t_filew		*tmp;

	tmp = path->files;
	if ((ft_strcmp(path->name, ".") != 0 && ft_strcmp(path->name, "..") != 0
			&& !is_request_path(env, path->name)) || env->show_path_name)
		ft_putendl(ft_strjoin(path->name, ":"));
	while (tmp != NULL)
	{
		show_file(env, path, tmp);
		tmp = tmp->next;
	}
	ft_putstr("\n");
	if (path->files)
		free_files(path->files);
}
