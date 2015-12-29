/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 13:48:17 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 15:14:42 by vmarchau         ###   ########.fr       */
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
	ft_putendl("-- START RENDER --");
	env->mlx = mlx_init();
	env->display = mlx_new_window(env->mlx, 500, 500, "Fdf");
	if (env->mlx == NULL || env->display == NULL)
		return (ft_error("ERROR"));
	mlx_key_hook(env->display, &onKeyPress, env);
	render(env);
	mlx_loop(env->mlx);
	return (0);
}
