/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:43:01 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/24 16:05:14 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	ft_memset(dest, '\0', len);
	while (i < len && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
