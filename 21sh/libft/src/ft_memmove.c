/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:46:29 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/24 13:15:39 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t			i;
	char			*desti;
	char			*source;
	char			*tmp;

	i = 0;
	desti = (char *)dest;
	source = (char *)src;
	tmp = (char *)malloc(sizeof(src));
	if (tmp == NULL || !dest || !src || size <= 0)
		return (dest);
	while (i < size)
	{
		tmp[i] = source[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		desti[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (dest);
}
