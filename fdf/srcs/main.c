/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 13:48:17 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/30 14:16:22 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fcntl.h"
#include "X.h"

int		ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

#include <stdio.h>
int		parse_args(t_env *env, int size, char **args)
{
	int i;

	i = 2;
	env->win_x = 500;
	env->win_y = 500;
	while (i < size)
	{
		if (ft_strfind(args[i], "-width") != NULL)
			env->win_x = ft_atoi(ft_strfind(args[i], "-width"));
		if (ft_strfind(args[i], "-height") != NULL)
			env->win_y = ft_atoi(ft_strfind(args[i], "-height"));
		i++;
	}
	env->cursr_x = env->win_x / 2;
	env->cursr_y = env->win_y / 2;
	return (1);
}

int		main(int size, char **args)
{
	int		fd;
	t_env	*env;
	
	if (size < 2 || !(env = (t_env*)malloc(sizeof(t_env))))
		return (ft_error("ERROR"));
	if ((fd = open(args[1], O_RDONLY)) == -1)
		return (ft_error("ERROR"));	
	if (!parse(fd, env))
		return (ft_error("ERROR"));
	parse_args(env, size, args);
	ft_putendl("RENDERING ..");
	env->mlx = mlx_init();
	env->display = mlx_new_window(env->mlx, env->win_x, env->win_y, "Fdf");
	if (env->mlx == NULL || env->display == NULL)
		return (ft_error("ERROR"));

	mlx_key_hook(env->display, &onKeyPress, env);
	render(env);
	mlx_loop(env->mlx);
	return (0);
}
