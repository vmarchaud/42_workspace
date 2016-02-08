/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:28:58 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/25 11:32:11 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t lendst;
	size_t lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size <= lendst)
		return (size + lensrc);
	if (lensrc < size - lendst)
	{
		ft_memcpy(dst + lendst, src, lensrc);
		dst += lendst + lensrc;
	}
	else
	{
		ft_memcpy(dst + lendst, src, size - lendst - 1);
		dst += size - 1;
	}
	*dst = '\0';
	return (lensrc + lendst);
}
