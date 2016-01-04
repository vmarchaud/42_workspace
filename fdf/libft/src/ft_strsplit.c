/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:26:18 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/04 14:36:17 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static int    ft_wcount(char const *s, char c)
{
	int    i;
	int    counter;

	i = 0;
	counter = 0;
	if (s[i] == 0 || (s[i] != c && i == 0))
		counter++;
	while (s[i] != 0)
	{
		i++;
		if (s[i] != c && s[i - 1] == c)
			counter++;
	}
	return (counter);
}

char        **ft_strsplit(char const *s, char c)
{
	int        i;
	int        j;
	int        k;
	char    **tab;

	i = 0;
	k = 0;
	if ((tab = (char **)malloc(sizeof(char*) * ft_wcount(s, c))) == NULL)
		return (NULL);
	while (s[i] == c)
		i++;
	while (s[i] != 0)
	{
		if ((s[i] != c && s[i - 1] == c) || (s[i] != c && i == 0))
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != 0)
				j++;
			tab[k++] = ft_strsub(s, i, j);
		}
		i++;
	}
	tab[k] = 0;
	return (tab);
}
