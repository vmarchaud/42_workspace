/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:12:49 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/28 13:02:23 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	put_tetris(t_map *map, t_tris *tris)
{
	int i;

	i = 0;
	while (i < 4)
	{
		map->map[map->y + tris->py[i]][map->x + tris->px[i]] = tris->idx + 'A';
		i++;
	}
}

int		place_it(t_map *map, int i)
{
	map->y = 0;
	while (map->y < map->w)
	{
		map->x = 0;
		while (map->x < map->w)
		{
			if (is_putable(map, map->tab[i]) > 0)
			{
				put_tetris(map, map->tab[i]);
				map->tab[i]->plcx = map->x;
				map->tab[i]->plcy = map->y;
				return (1);
			}
			map->x++;
		}
		map->y++;
	}
	return (0);
}

int		clear_it(t_map *map, int i)
{
	int		j;
	int		k;

	j = 0;
	while (j < map->w)
	{
		k = 0;
		while (k < map->w)
		{
			if (map->map[j][k] == 'A' + i)
				map->map[j][k] = '.';
			k++;
		}
		j++;
	}
	return (0);
}

int		move_it(t_map *map, int i)
{
	clear_it(map, i);
	map->x = map->tab[i]->plcx + 1;
	map->y = map->tab[i]->plcy;
	while (map->y < map->w)
	{
		while (map->x < map->w)
		{
			if (is_putable(map, map->tab[i]) > 0)
			{
				put_tetris(map, map->tab[i]);
				map->tab[i]->plcx = map->x;
				map->tab[i]->plcy = map->y;
				return (1);
			}
			map->x++;
		}
		map->x = 0;
		map->y++;
	}
	return (0);
}

int		resolve(t_map *map, int i)
{
	if (i == map->nb)
		return (1);
	if (!place_it(map, i))
		return (0);
	while (!resolve(map, i + 1))
	{
		if (move_it(map, i))
			continue ;
		return (0);
	}
	return (1);
}
