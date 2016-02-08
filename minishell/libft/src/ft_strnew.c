/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:35:58 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/20 15:22:23 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*buffer;
	size_t	i;

	if ((buffer = (char *)malloc(size)) == 0)
		return (NULL);
	i = 0;
	while (i < size)
		buffer[i++] = 0;
	return (buffer);
}
