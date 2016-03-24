/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_leftpad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:42:55 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/24 14:16:32 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_leftpad(char *str, size_t start, size_t padding)
{
	size_t	i;
	size_t	tmp;

	if (ft_strlen(str + start)  < padding + 1)
		return (str);
	i = start;
	tmp = ft_strlen(str);
	while (str[i + padding])
	{
	 	str[i] = str[i + padding];
		i++;
	}
	str[tmp - 1] = 0;
	return (str);
}
