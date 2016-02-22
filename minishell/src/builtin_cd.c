/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 13:24:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/22 13:38:26 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd_home(t_global *gbl)
{

}

void	builtin_cd(t_global *gbl, int size, char **args)
{
	if (size >= 3)
		return (ft_putendl_fd("cd: too much args", 2));
	if (size == 1)
		return (builtin_cd_home(gbl));
	if (access(args[0], F_OK) != 0)
		return (ft_putendl_fd("cd: directory doesnt exist", 2));
	if (access(args[0], X_OK) != 0)
		return (ft_putendl_fd("cd: permission denied", 2));
	chdir(args[0]);
		
}
