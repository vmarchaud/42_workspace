/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:14:31 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/21 13:48:55 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int const fd, char **line)
{
	int				ret;
	char			*tmp;
	char			buffer[BUFF_SIZE + 1];
	static char		*str[255];

	if (BUFF_SIZE <= 0 || !line || fd < 0 ||
			!(str[fd] = !str[fd] ? ft_strnew(1) : str[fd]))
		return (-1);
	while (!ft_strchr(str[fd], '\n') && (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		tmp = str[fd];
		buffer[ret] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer);
		free(tmp);
	}
	if (ft_strchr(str[fd], '\n'))
		*line = ft_strsub(str[fd], 0, ft_strchr(str[fd], '\n') - str[fd]);
	else
		*line = ft_strdup(str[fd]);
	if (ft_strchr(str[fd], '\n'))
		str[fd] = ft_strsub(str[fd], ft_strchr(str[fd], '\n') - str[fd] + 1,
				ft_strlen(ft_strchr(str[fd], '\n')));
	if (ret == -1)
		return (-1);
	return (!ret && !ft_strlen(str[fd]) && !ft_strlen(*line) ? 0 : 1);
}
