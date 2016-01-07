/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:26:18 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/07 12:45:53 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_strsplitcpy(char const *s, char c, char **tab)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i + j++] != c)
			if (!s[i + j])
				break ;
		tab[k] = (char*)malloc(sizeof(char) * (j + 1));
		j = 0;
		while (s[i] != c && s[i])
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		k++;
	}
	tab[k] = 0;
	return (tab);
}

static int		ft_split_len(const char *str, char c)
{
	int		len;
	int		i;

	len = 1;
	i = 0;
	while (c && ft_strchr(str + i, c))
	{
		while (str[i] == c && str[i])
			++i;
		if (str[i] != c)
			++len;
		while (str[i] != c && str[i])
			++i;
	}
	return (len);
}

char			**ft_strsplit(const char *str, char c)
{
	char	**tab;
	int		len;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == c)
		i++;
	if (!str[i])
		return (ft_memalloc(sizeof(char*)));
	len = ft_split_len(str, c) + 1;
	tab = (char**)ft_memalloc(len * sizeof(char*));
	ft_strsplitcpy(str, c, tab);
	return (tab);
}
