/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:34:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/11 15:14:24 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exit_clean(int error, char *reason, t_env *env)
{
	if (error)
		ft_putstr("ERROR : ");
	ft_putendl(reason);
	free(env);
	exit(0);
}

int		main(int size, char **args)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit_clean(1, "cant malloc struct", env);
	if (!parse(env, size, args))
		exit_clean(1, "parsing failed", env);
	return (0);
}
