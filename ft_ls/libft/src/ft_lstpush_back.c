/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 11:31:54 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/10 11:36:25 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpush_back(t_list *lst, t_list *elem)
{
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = elem;
}
