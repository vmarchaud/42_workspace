/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:14:11 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/28 11:53:53 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

int		verify_args(int size, char **args)
{
	int fd;

	if (size != 2 && !ft_strfind(args[2], "-color"))
	{
		ft_putstr_fd("error\n", 1);
		return (-1);
	}
	if ((fd = open(args[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("error\n", 1);
		return (-1);
	}
	return (fd);
}

int		main(int size, char **args)
{
	t_map	*map;
	int		fd;

	if ((fd = verify_args(size, args)) < 0)
		return (0);
	if ((map = parse(fd, 0)) == NULL)
	{
		ft_putstr_fd("error\n", 1);
		return (0);
	}
	
	while (!resolve(map, 0))
		map->w++;
	map->color = 0;
	if (args[2] && ft_strfind(args[2], "-color"))
		map->color = 1;
	show_map(map);
	return (0);
}
