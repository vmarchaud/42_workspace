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

static size_t		ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if ((i == 1 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int			ft_is_begin_word(char const *s, size_t index, char c)
{
	if (index == 0 && s[index] != c)
		return (1);
	if (s[index] != c && s[index - 1] == c)
		return (1);
	return (0);
}

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
