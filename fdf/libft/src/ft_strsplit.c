/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:26:18 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/27 11:31:18 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	i = 0;
	k = 0;
	if ((tab = (char **)malloc(sizeof(char *) * ft_count_word(s, c))) == NULL)
		return (NULL);
	if (ft_count_word(s, c) == 0)
		return (tab);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		j = 0;
		if (ft_is_begin_word(s, i, c))
		{
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			tab[k++] = ft_strsub(s, i, j);
		}
		i++;
	}
	return (tab);
}
