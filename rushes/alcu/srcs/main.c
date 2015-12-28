/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 12:11:07 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/21 13:52:02 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include <fcntl.h>

int		ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	return (-1);
}

int		main(int len, char **args)
{
	int		fd;
	t_env	*env;

	if (len == 1)
		fd = 0;
	else if ((fd = open(args[1], O_RDONLY)) == -1)
		return (ft_error("ERROR"));
	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (ft_error("ERROR"));
	if (!parse(fd, env))
		return (ft_error("ERROR"));
	close(fd);
	show_map(env);
	if (!play(env))
		return (ft_error("ERROR"));
	ft_putstr("THE WINNER IS THE ");
	if (env->turn == 0)
		ft_putendl("PLAYER !");
	else
		ft_putendl("IA !");
	return (0);
}
