/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 14:28:59 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/11 15:20:45 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path		*ft_newpath(char *name)
{
	t_path *path = NULL;

	if ((path = (t_path*)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	path->name = name;
	path->dir = NULL;
	path->next = NULL;
	return (path);
}
