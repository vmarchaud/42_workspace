/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:12:12 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/25 13:56:59 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hist	*new_hist(char *cmd)
{
	t_hist	*new;

	if ((new = malloc(sizeof(t_cmd))) == NULL)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_hist	*add_hist(t_hist *head, t_hist *value)
{
	t_hist	*tmp;

	tmp = head->next;
	value->next = tmp;
	if (tmp)
	{
		tmp->prev = value;
	}
	head->next = value;
	value->prev = head;
	return (head);
}

t_hist	*find_hist(t_hist *head, char *str)
{
	t_hist	*tmp;

	tmp = head;
	if (!head)
		return (NULL);
	else
		while (tmp)
		{
			if (ft_strmatches(str, tmp->cmd) == 0)
				return (tmp);
			tmp = tmp->next;
		}
	return (NULL);
}

t_hist	*reset_hist(t_hist *head)
{
	t_hist	*tmp;

	tmp = head;
	while (tmp->prev)
		tmp = tmp->prev;
	head = tmp;
	return (head);
}

void	print_history(t_hist *head)
{
	int		i;
	t_hist	*tmp;

	i = 0;
	ft_putendl("");
	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		ft_putnbr(i);
		ft_putchar('\t');
		ft_putendl(tmp->cmd);
		tmp = tmp->next;
		i++;
	}
}
