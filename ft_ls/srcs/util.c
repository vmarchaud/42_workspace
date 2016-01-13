/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:35:14 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/13 14:31:40 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_hidden(char *name)
{
	if (ft_strcmp(name, ".") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "..") == 0)
		return (TRUE);
	else if (*name == '.')
		return (TRUE);
	else
		return (FALSE);
}
