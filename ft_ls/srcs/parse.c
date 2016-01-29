/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:21:26 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/29 16:06:06 by vmarchau         ###   ########.fr       */
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
			exit_clean(1, &arg[i], env);
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
	free(stat);
	return (0);
}

void		addfile_to_env(t_env *env, char *path)
{
	t_filew		*tmp;
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
	new->path = ft_strsub(path, 0,  ft_strrchr(path, '/') - path);
	new->type = NULL;
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

int			parse(t_env *env, int size, char **args)
{
	int		i;
	int 	ret;

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
		}
		i++;
	}
	if (env->paths == NULL && env->files == NULL)
		ft_addpath_env(env, ".");
	return (TRUE);
}
