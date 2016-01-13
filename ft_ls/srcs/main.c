/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:34:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/13 13:37:40 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		exit_clean(int error, char *reason, t_env *env)
{
	(void)env;
	if (error)
		ft_putstr("ERROR : ");
	ft_putendl(reason);
	exit(0);
}

void		show_dirs(t_env *env)
{
	t_path		*tmp;

	tmp = env->paths;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, ".") != 0 && *(tmp->name) != '/')
			ft_putendl(ft_strjoin(tmp->name, ":"));
		show_dir(env, tmp);
		if (tmp->next != NULL)
			ft_putstr("\n\n");
		tmp = tmp->next;
	}
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

int			main(int size, char **args)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit_clean(1, "cant malloc struct", env);
	if (!parse(env, size, args))
		exit_clean(1, "parsing failed", env);
	compute_dirs(env);
	show_dirs(env);
	return (0);
}
