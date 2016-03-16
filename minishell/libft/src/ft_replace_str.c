/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:32:27 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/16 14:43:10 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_str(char *str, char *pattern, char *repl)
{
	char	*tmp;
	char	*buff;
	char	*del;

	while (ft_strstr(str, pattern) != NULL)
	{
		tmp = ft_strdup(str);
		buff = ft_strstr(tmp, pattern);
		*buff = 0;
		buff = ft_strjoin(tmp, repl);
		free(tmp);
		del = buff;
		if (*(ft_strstr(str, pattern) + ft_strlen(pattern)) != 0)
		{
			buff = ft_strjoin(buff, ft_strstr(str, pattern)
					+ ft_strlen(pattern));
			free(del);
		}
		free(str);
		str = buff;
	}
	return (str);
}
