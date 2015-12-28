/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:12:49 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/19 14:35:46 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		is_correct_form(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '#')
			if (is_char_near(str, '#', i) < 2)
				count++;
		if (str[i] == '#' && is_char_near(str, '#', i) == 0)
			return (-1);
		i++;
	}
	return (count > 3 ? -1 : 0);
}

int		ft_srch_newl(char *str)
{
	if (str[4] != '\n' || str[9] != '\n' || str[14] != '\n' || str[19] != '\n')
		return (-1);
	return (1);
}

t_map	*verify(t_tris *lst, size_t count)
{
	char	index;
	t_map	*map;
	t_tris	**tab;

	index = 0;
	if ((map = malloc(sizeof(t_map))) == NULL ||
		(tab = (t_tris **)malloc(sizeof(t_tris *) * count)) == 0)
		return (NULL);
	while (lst != NULL)
	{
		if (ft_count_char(lst->content, '#') != 4)
			return (NULL);
		if (ft_count_char(lst->content, '.') != 12)
			return (NULL);
		if (ft_srch_newl(lst->content) < 0)
			return (NULL);
		if (is_correct_form(lst->content) == -1)
			return (NULL);
		tab[index] = lst;
		lst->idx = index++;
		compute_index(lst);
		lst = lst->next;
	}
	setup_map(map, count, tab);
	return (map);
}

t_map	*parse(int fd, int count)
{
	char		buffer[21];
	size_t		in;
	t_tris		*first;
	t_tris		*list;
	t_map		*map;

	if ((in = read(fd, buffer, 21)) > 0)
		list = ft_newtris(buffer, 21);
	else
		return (NULL);
	first = list;
	ft_bzero(buffer, 21);
	count = 1;
	while ((in = read(fd, buffer, 21)) > 0)
	{
		list->next = ft_newtris(buffer, 21);
		count++;
		ft_bzero(buffer, 21);
		list = list->next;
	}
	if (list->content[20] == '\n' || count > 26)
		return (NULL);
	return (map = verify(first, count));
}
