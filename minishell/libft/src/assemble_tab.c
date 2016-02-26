/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:44:12 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 15:27:52 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int    st_getlen(char const **table, int patern_len)
{
	int        ret;
	int        overflow;
	int        i;

	i = 0;
	ret = 1 - patern_len;
	while (table[i])
	{
		overflow = ret;
		ret += strlen(table[i]) + patern_len;
		i++;
		if (overflow > ret)
			return (-1);
	}
	return (ret);
}

char        *assemble_tab(char const **table, char const *patern)
{
	char    *new;
	int        i;

	i = st_getlen(table, ft_strlen(patern));
	if (i < 0)
		return (NULL);
	if ((new = malloc(sizeof(char) * i)))
	{
		i = 0;
		*new = '\0';
		while (table[i])
		{
			ft_strcat(new, table[i++]);
			if (table[i])
				ft_strcat(new, patern);
		}
	}
	return (new);
}
