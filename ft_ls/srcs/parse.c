/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:21:26 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/03 15:32:22 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		parse_arg(t_env *env, char *arg)
{
	size_t		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 'l')
			env->format_out = TRUE;
		else if (arg[i] == 'R')
			env->recursive = TRUE;
		else if (arg[i] == 'a')
			env->show_dot = TRUE;
		else if (arg[i] == 'r')
			env->reverse = TRUE;
		else if (arg[i] == 't')
			env->sort_time = TRUE;
		else
			exit_clean(1, ft_strjoin("illegal option -- ", arg), env);
		i++;
	}
}

int			check_exist(char *path)
{
	struct stat		*stat;

	if ((stat = malloc(sizeof(struct stat))) == NULL)
		return (-1);
	if (lstat(path, stat) == -1)
	{
		perror(path);
		free(stat);
		return (-1);
	}
	else if (S_ISDIR(stat->st_mode))
	{
		free(stat);
		return (1);
	}
	else if (S_ISLNK(stat->st_mode))
	{
		free(stat);
		return (3);
	}
	free(stat);
	return (0);
}

void		pushfile(t_env *env, t_filew *new)
{
	t_filew *tmp;

	if (env->files == NULL)
		env->files = new;
	else
	{
		tmp = env->files;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		addfile_to_env(t_env *env, char *path)
{
	t_filew		*new;
	int			i;
	char		**tab;

	if ((new = malloc(sizeof(t_filew))) == NULL)
		return ;
	tab = ft_strsplit(path, '/');
	i = 0;
	while (tab[i])
		i++;
	new->name = ft_strdup(tab[i - 1]);
	if ((new->stat = malloc(sizeof(struct stat))) == NULL)
		return ;
	lstat(path, new->stat);
	new->next = NULL;
	if (ft_strchr(path, '/'))
		new->path = ft_strsub(path, 0, ft_strrchr(path, '/') - path);
	else
		new->path = NULL;
	new->type = NULL;
	pushfile(env, new);
}

int			parse(t_env *env, int size, char **args)
{
	int		i;
	int		ret;

	i = 1;
	while (i < size)
	{
		if (*args[i] == '-' && env->paths == NULL)
			parse_arg(env, args[i] + 1);
		else
		{
			if (env->paths != NULL)
				env->show_path_name = TRUE;
			ret = check_exist(args[i]);
			if (ret == 1)
				ft_addpath_env(env, args[i]);
			else if (ret == 0)
				addfile_to_env(env, args[i]);
			else if (ret == 3 && !env->format_out)
				ft_addpath_env(env, get_real_path(args[i]));
			else if (ret == 3)
				addfile_to_env(env, args[i]);
		}
		i++;
	}
	if (env->paths == NULL && env->files == NULL && ret != -1)
		ft_addpath_env(env, ".");
	return (TRUE);
}
