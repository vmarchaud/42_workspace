/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 14:24:09 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/01 14:29:47 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_link(t_path *path, t_filew *file)
{
	char	result[256];
	int		ret;

	ret = readlink(ft_strjoins(path->name, "/", file->name), result, 256);
	result[ret] = 0;
	ft_putstr(file->name);
	ft_putstr(" -> ");
	ft_putendl(result);
}

void		print_major_minor(dev_t st_rdev)
{
	ft_putnbr(major(st_rdev));
	ft_putstr(", ");
	ft_putnbr(minor(st_rdev));
}
