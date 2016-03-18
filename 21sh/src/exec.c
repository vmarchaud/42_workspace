/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 11:55:17 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/17 11:48:44 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_type(char *path)
{
	int				ret;
	t_stat			*stat;

	if ((stat = malloc(sizeof(struct stat))) == NULL)
		return (-1);
	if (lstat(path, stat) == -1)
		ret = 0;
	else if (S_ISDIR(stat->st_mode))
		ret = 2;
	else if (S_ISLNK(stat->st_mode))
		ret = 3;
	else if (S_ISREG(stat->st_mode))
		ret = 1;
	else
		ret = 0;
	free(stat);
	return (ret);
}

char	*check_with_env(t_global *gbl, char *name)
{
	int		i;
	char	**tab;
	t_env	*entry;
	char	*ret;

	if ((entry = find_entry(gbl, "PATH")) == NULL)
		return (NULL);
	tab = ft_strsplit(entry->value, ':');
	i = 0;
	while (tab[i])
	{
		if (get_type((ret = strjoins(tab[i], "/", name))) == 1)
		{
			ft_freetab(tab);
			return (ret);
		}
		else
			free(ret);
		i++;
	}
	ft_freetab(tab);
	return (NULL);
}

void	execute(t_global *gbl, char *path, char **args, char **tab)
{
	(void)gbl;
	if (access(path, X_OK) != 0)
		return (ft_putendl_fd("Permission denied", 2));
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(path, args, tab);
		exit(0);
	}
	signal(SIGINT, &sighandler);
	wait(NULL);
	signal(SIGINT, SIG_IGN);
	free(path);
}

int		execute_cmd(t_global *gbl, int size, char **args, char **tab)
{
	int		ret;
	char	*path;

	(void)size;
	ret = get_type(args[0]);
	if (ret == 2 || ret == 3)
		builtin_cd_here(gbl, args[0]);
	else if (ret == 1)
		execute(gbl, ft_strdup(args[0]), args, tab);
	else if (ret == 0 && (path = check_with_env(gbl, *args)) != NULL)
		execute(gbl, path, args, tab);
	else
		ft_putendl("command not found");
	return (0);
}
