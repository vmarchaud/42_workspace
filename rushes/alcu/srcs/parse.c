/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 12:24:02 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/21 12:26:49 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

void	show_map(t_env *env)
{
	int i;
	int j;

	i = 0;
	while (i < env->len)
	{
		j = 0;
		while (j < i)
		{
			ft_putchar(' ');
			j++;
		}
		ft_putendl(env->map[i++]);
	}
}

char	*setup_line(int nb)
{
	int		i;
	char	*str;

	i = 0;
	if ((str = ft_strnew(nb + 2)) == NULL)
		return (NULL);
	while (i < nb)
		str[i++] = '|';
	return (str);
}

int		setup_map(t_env *env, t_list *tmp)
{
	int		i;
	int		nb;

	i = 0;
	if ((env->map = (char **)malloc(sizeof(char *) * env->len)) == NULL)
		return (0);
	while (tmp != NULL)
	{
		nb = ft_atoi(tmp->content);
		if (nb < 1 || nb > 10000 || !ft_isnumeric(tmp->content))
			return (0);
		env->map[i] = setup_line(nb);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int		parse(int const fd, t_env *env)
{
	char	*line;
	t_list	*first;
	t_list	*tmp;

	env->len = 1;
	if ((line = (char *)malloc(sizeof(char) * 100)) == NULL)
		return (0);
	if (get_next_line(fd, &line) > 0)
		tmp = ft_lstnew(line, ft_strlen(line));
	else
		return (0);
	first = tmp;
	while (get_next_line(fd, &line) > 0)
	{
		if (fd == 0 && ft_strlen(line) == 0)
			break ;
		tmp->next = ft_lstnew(line, ft_strlen(line));
		tmp = tmp->next;
		env->len++;
	}
	return (setup_map(env, first));
}
