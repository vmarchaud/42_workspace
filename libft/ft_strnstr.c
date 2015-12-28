/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:25:10 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/25 11:28:20 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
	{
		if (!s2)
			return ((char *)s1);
		while (s1[i] != '\0' && i < n)
		{
			j = 0;
			while (s1[i + j] && (i + j) < n && s1[i + j] == s2[j])
				j++;
			if (s2[j] == '\0')
				return ((char *)&s1[i]);
			i++;
		}
	}
	return (NULL);
}
