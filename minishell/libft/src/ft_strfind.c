/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 12:34:00 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/30 14:06:35 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strfind(char *str1, char *str2)
{
	int i;
	int j;
	int size;

	size = 0;
	while (str2[size] != '\0')
		size++;
	if (size == 0)
		return (str1);
	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		while (str1[i + j] == str2[j])
		{
			j++;
			if (j == size)
				return (str1 + i + j);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
