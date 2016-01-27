/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:34:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 13:36:46 by vmarchau         ###   ########.fr       */
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

int			main(int size, char **args)
{
	t_env	*env;
	t_path	*tmp;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit_clean(1, "cant malloc struct", env);
	if (!parse(env, size, args))
		exit_clean(1, "parsing failed", env);
	tmp = env->paths;
	while (tmp != NULL)
	{
		compute_dir(env, tmp);
		tmp = tmp->next;
	}
	return (0);
}
