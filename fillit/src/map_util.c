/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:12:49 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/18 14:50:57 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	show_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->w)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->color == 1)
			{
				if (map->map[i][j] == '.')
					ft_putstr(map->colors[15]);
				else if ((map->map[i][j] - 'A') > 15)
					ft_putstr(map->colors[(map->map[i][j] - 'A' - 15)]);
				else
					ft_putstr(map->colors[(map->map[i][j] - 'A')]);
			}
			ft_putchar(map->map[i][j]);
			j++;
		}
		i++;
		ft_putchar('\n');
	}
}

void	setup_map(t_map *map, int count, t_tris **tab)
{
	int i;
	int x;
	int nb;

	map->nb = count;
	map->tab = tab;
	nb = count;
	i = 0;
	nb *= 4;
	while (i * i < nb)
		i++;
	nb = i;
	i = 0;
	while (i < 16)
	{
		x = 0;
		while (x < 16)
			map->map[i][x++] = '.';
		i++;
	}
	map->w = nb;
	init_colors(map);
}

void	init_colors(t_map *map)
{
	map->colors = (char **)malloc(sizeof(char *) * 16);
	map->colors[0] = BLACK;
	map->colors[1] = RED;
	map->colors[2] = GREEN;
	map->colors[3] = YELLOW;
	map->colors[4] = BLUE;
	map->colors[5] = PURPLE;
	map->colors[6] = CYAN;
	map->colors[7] = GREY;
	map->colors[8] = GREYB;
	map->colors[9] = REDB;
	map->colors[10] = GREENB;
	map->colors[11] = YELLOW;
	map->colors[12] = BLUEB;
	map->colors[13] = PURPLEB;
	map->colors[14] = CYANB;
	map->colors[15] = GREYB;
}

t_tris	*ft_newtris(void const *content, size_t content_size)
{
	t_tris	*elem;

	if ((elem = (t_tris *)malloc(sizeof(t_tris))) == 0)
		return (NULL);
	if (content == NULL)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		elem->content = ft_memcpy(ft_memalloc(content_size),
			content, content_size);
		elem->content_size = content_size;
	}
	elem->next = NULL;
	elem->w = 0;
	elem->h = 0;
	return (elem);
}
