/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:59:51 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/24 13:14:25 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t		i;
	char		*desti;
	char		*source;

	i = 0;
	desti = (char *)dest;
	source = (char *)src;
	if (size == 0 || !desti || !source)
		return (dest);
	while (i < size)
	{
		desti[i] = source[i];
		i++;
	}
	return (dest);
}
