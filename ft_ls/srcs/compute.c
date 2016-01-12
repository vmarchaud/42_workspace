/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:37:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/12 15:56:17 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char		*ft_strjoins(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

void		compute_dir(t_env *env, t_path *path)
{
	struct dirent	*tmp;
	DIR				*dir;

	if ((dir = opendir(path->name)) == NULL)
	{
		perror("ERROR");
		return ;
	}
	path->files = NULL;
	while ((tmp = readdir(dir)) != NULL)
	{
		if (env->recursive && tmp->d_type == DT_DIR)
			ft_addpath(env, ft_strjoins(path->name, "/", tmp->d_name));
		ft_addfile(path, tmp);
	}
	closedir(dir);
}

void		compute_dirs(t_env *env)
{
	t_path *tmp;

	tmp = env->paths;
	while (tmp != NULL)
	{
		compute_dir(env, tmp);
		tmp = tmp->next;
	}
}

void		show_dir(t_env *env, t_path *path)
{
	t_filew		*tmp;

	tmp = path->files;
	while (tmp != NULL)
	{
		ft_putstr(tmp->file->d_name);
		ft_putchar('\t');
		tmp = tmp->next;
	}
}

void		show_dirs(t_env *env)
{
	t_path		*tmp;

	tmp = env->paths;
	while (tmp != NULL)
	{
		ft_putendl(tmp->name);
		show_dir(env, tmp);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
