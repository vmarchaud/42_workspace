/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 13:24:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/14 13:49:22 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		verify_access(char *path)
{
	struct stat		*stat;

	if ((stat = malloc(sizeof(struct stat))) == NULL)
		return (0);
	if (access(path, F_OK) != 0)
		ft_putendl_fd("cd: directory cant be accessed", 2);
	else if (lstat(path, stat) < 0)
		ft_putendl_fd("cd: permission denied", 2);
	else if (!S_ISDIR(stat->st_mode) && !S_ISLNK(stat->st_mode))
		ft_putendl_fd("cd: cannot cd in this type", 2);
	else if (access(path, X_OK) != 0)
		ft_putendl_fd("cd: permission denied", 2);
	else
		return (1);
	return (0);
}

void	builtin_cd_here(t_global *gbl, char *path)
{
	char	**tab;

	if ((tab = malloc(sizeof(char*) * 3)) == NULL)
		return ;
	tab[0] = ft_strdup("cd");
	tab[1] = path;
	tab[2] = NULL;
	builtin_cd(gbl, 2, tab);
}

void	builtin_cd(t_global *gbl, int size, char **args)
{
	t_env	*entry;

	if (size >= 3)
		return (ft_putendl_fd("cd: too much args", 2));
	if (size == 1)
		args[1] = ft_strdup("~");
	entry = find_entry(gbl, "HOME");
	if (ft_strchr(args[1], '~') && entry != NULL)
		args[1] = strreplace_once(args[1], "~", entry->value);
	if (!verify_access(args[1]))
		return ;
	entry = find_entry(gbl, "PWD");
	if (entry != NULL)
		put_entry(gbl, "OLDPWD", entry->value);
	chdir(args[1]);
	put_entry(gbl, "PWD", getcwd(NULL, 0));
	update_tabenv(gbl);
}
