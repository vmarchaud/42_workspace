/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 13:24:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/22 16:27:29 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd_home(t_global *gbl)
{

}

void	builtin_cd(t_global *gbl, int size, char **args)
{
	t_env	*entry;

	if (size >= 3)
		return (ft_putendl_fd("cd: too much args", 2));
	if (size == 1)
		return (builtin_cd_home(gbl));
	if (access(args[0], F_OK) != 0)
		return (ft_putendl_fd("cd: directory doesnt exist", 2));
	if (access(args[0], X_OK) != 0)
		return (ft_putendl_fd("cd: permission denied", 2));
	entry = find_entry(gbl, "HOME");
	if (ft_strchr(args[0], '~') && entry != NULL)
		args[0] = strreplace(args[0], "~", entry->value);
	chdir(args[0]);
}
