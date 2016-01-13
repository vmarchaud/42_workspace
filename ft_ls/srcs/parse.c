/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:21:26 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/13 13:15:01 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			exit_clean(1, "illegal option", env);
		i++;
	}
}

int			parse(t_env *env, int size, char **args)
{
	int		i;

	i = 1;
	env->recursive = FALSE;
	env->sort_time = FALSE;
	env->show_dot = FALSE;
	env->reverse = FALSE;
	env->format_out = FALSE;
	env->paths = NULL;
	while (i < size)
	{
		if (!ft_strchr(args[i], '-'))
			ft_addpath(env, args[i]);
		else
			parse_arg(env, args[i] + 1);
		i++;
	}
	if (env->paths == NULL)
		ft_addpath(env, ".");
	return (TRUE);
}
