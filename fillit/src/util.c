/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 15:19:41 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/18 13:43:50 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		is_char_near(char *str, char c, size_t index)
{
	int count;

	count = 0;
	if (str[index - 1] == c)
		count++;
	if (str[index + 1] == c)
		count++;
	if (str[index - 5] == c)
		count++;
	if (str[index + 5] == c)
		count++;
	return (count);
}

void	compute_position(t_tris *lst, int pos)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (lst->content[pos + y * 5 + x] == '#')
			{
				lst->px[i] = x;
				lst->py[i] = y;
				i++;
			}
			y++;
		}
		x++;
	}
	return (compute_size(lst));
}

void	compute_size(t_tris *lst)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (i < 4)
	{
		if (lst->px[i] > max)
			max = lst->px[i];
		i++;
	}
	lst->w = max;
	i = 0;
	max = 0;
	while (i < 4)
	{
		if (lst->py[i] > max)
			max = lst->py[i];
		i++;
	}
	lst->h = max;
}

void	compute_index(t_tris *lst)
{
	int i;
	int j;

	i = 0;
	if (lst->content[18] == '#' && lst->content[3] == '#')
		return (compute_position(lst, 3));
	if (lst->content[18] == '#' && lst->content[15] == '#')
		return (compute_position(lst, 15));
	while (i < 4 && !(j = 0))
	{
		while (j < 4)
		{
			if (lst->content[i * 5 + j] == '#')
				return (compute_position(lst, i * 5 + j));
			if ((lst->content[i * 5 + j + 1] == '#' ||
				lst->content[i * 5 + j + 2] == '#') &&
				lst->content[i * 5 + j + 1] != '\n')
				if (lst->content[(i + 1) * 5 + j] == '#' ||
					(i < 2 && lst->content[(i + 2) * 5 + j] == '#'))
					return (compute_position(lst, i * 5 + j));
			j++;
		}
		i++;
	}
}

char	free_ptr(void *ptr)
{
	free(ptr);
	return (0);
}
