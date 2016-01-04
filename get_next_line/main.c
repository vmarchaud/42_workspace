/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 11:10:30 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/04 12:38:10 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

int		main(int size, char **args)
{
	int 	fd;
	char	*line;
	int		i;

	(void)size;
	i = 0;
	fd = open(args[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putnbr(i);
		ft_putchar('\t');
		ft_putendl(line);
		free(line);
		i++;
	}
	return (0);
}
