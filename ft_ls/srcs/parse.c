/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:21:26 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/11 15:17:56 by vmarchau         ###   ########.fr       */
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
	size_t	i;
	t_path	*tmp;

	i = 1;
	tmp = ft_newpath("");
	env->paths = tmp;
	while (i < size)
	{
		if (!ft_strchr(args[i], '-'))
		{
			tmp->next = ft_newpath(args[i]);
			tmp = tmp->next;
		}
		else
			parse_arg(env, args[i] + 1);
		i++;
	}
	if (env->paths->next != NULL)
		env->paths = env->paths->next;
	return (TRUE);
}
