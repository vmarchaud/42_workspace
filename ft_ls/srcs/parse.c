/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:21:26 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 15:01:17 by vmarchau         ###   ########.fr       */
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
		}
		i++;
	}
	if (env->paths == NULL)
		ft_addpath_env(env, ".");
	return (TRUE);
}
