/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:14:31 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/06 15:36:01 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int		get_next_line(int const fd, char **line)
{
	int				ret = -1;
	char			*rm;
	char			buffer[BUFF_SIZE + 1];
	static char		*s[214748364];

	if (!line || fd < 0 || !(s[fd] = !s[fd] ? ft_strnew(1) : s[fd]))
		return (-1);
	while (!ft_strchr(s[fd], '\n') && (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		rm = s[fd];
		buffer[ret] = '\0';
		s[fd] = ft_strjoin(s[fd], buffer);
		free(rm);
	}
	if (ret == -1)
		return (-1);
	*line = (ft_strchr(s[fd], '\n') ? ft_strsub(s[fd], 0,
				ft_strchr(s[fd], '\n') - s[fd]) : ft_strdup(s[fd]));
	if (ft_strchr((rm = s[fd]), '\n'))
		s[fd] = ft_strsub(s[fd], ft_strchr(s[fd], '\n') - s[fd] + 1,
				ft_strlen(s[fd]));
	else
		s[fd] = ft_strsub(s[fd], ft_strlen(*line), ft_strlen(s[fd]));
	free(rm);
	ft_putnbr(ret);
	ft_putchar(' ');
	ft_putnbr(ret == 0);
	ft_putchar(' ');
	return (ret == 0 && !ft_strlen(s[fd]) && !ft_strlen(*line) ? 0 : 1);
}
