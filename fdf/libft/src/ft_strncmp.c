/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:11:25 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/25 14:34:06 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char const *str1, char const *str2, size_t nb)
{
	size_t i;

	i = 0;
	while (i < nb)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		if ((unsigned char)str1[i] == '\0' && (unsigned char)str2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
