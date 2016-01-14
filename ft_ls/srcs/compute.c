/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 11:37:00 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/14 15:16:10 by vmarchau         ###   ########.fr       */
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
		perror(path->name);
		return ;
	}
	path->files = NULL;
	while ((tmp = readdir(dir)) != NULL)
	{
		if (env->recursive && tmp->d_type == DT_DIR && !is_hidden(tmp->d_name))
			ft_addpath(env, ft_strjoins(path->name, "/", tmp->d_name));
		ft_addfile(path, tmp);
	}
	//sort_by_alpha(path);
	show_dir(env, path);
	closedir(dir);
}

void		show_dir(t_env *env, t_path *path)
{
	t_filew		*tmp;
	short		i;

	i = 0;
	tmp = path->files;
	while (tmp != NULL)
	{
		if (is_hidden(tmp->name) && !env->show_dot)
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
}
