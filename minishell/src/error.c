/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:14:21 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 12:23:34 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void		error(char	*msg)
{
		if (errno)
			write(2, msg, ft_strlen(msg));
		verify_io();
}

void		verify_io() {
	if (errno == EIO)
		write(2, "input/output error");
	else if (errno == ENANETOOLONG)
		write(2, "filename too long");
	else if (errno == ENOENT)
		write(2, "no such file or directory");
	else if (errno == ENODEV)
		write(2, "no such device");
	else if (errno == ENOTDIR)
		write(2, "not a directory");
}
