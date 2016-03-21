/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:49:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/21 15:43:04 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>

void	core(t_global *gbl)
{
	char	*line;
	int		i;
	char	**cmd;
	char	buff[21];
	
	while (42)
	{
		ft_putstr("$> ");
		i = 0;
		line = ft_strnew(1);
		while (ft_strchr(line, '\n') == NULL)
		{
			ft_bzero(buff, 21);
			read(0, buff, 20);
			line = handle_input(buff, line);
		}
		line = ft_replace_char(line, '\n', '\0');
		cmd = ft_strsplit(line, ';');
		while (cmd[i] != NULL)
			evaluate_line(gbl, cmd[i++]);
		free(line);
		ft_freetab(cmd);
	}
}

void	register_cmds(t_global *gbl)
{
	register_cmd(gbl, "env", &builtin_env);
	register_cmd(gbl, "exit", &builtin_exit);
	register_cmd(gbl, "setenv", &builtin_setenv);
	register_cmd(gbl, "unsetenv", &builtin_unsetenv);
	register_cmd(gbl, "cd", &builtin_cd);
	register_cmd(gbl, "alias", &builtin_alias);
	register_cmd(gbl, "unalias", &builtin_unalias);
	register_cmd(gbl, "aliaslst", &builtin_aliaslist);
	put_alias(gbl, ft_strdup("ls"), ft_strdup("ls -G"));
}

int		main(int size, char **args, char **env)
{
	t_global	*gbl;
	size_t		env_size;

	(void)size;
	(void)args;
	if ((gbl = malloc(sizeof(t_global))) == NULL)
		return (0);
	signal(SIGINT, SIG_IGN);
	env_size = array_size(env);
	gbl->env_size = env_size;
	gbl->env = tab_to_env(env, env_size);
	update_shell_lvl(gbl);
	gbl->tabenv = env_to_tab(gbl->env, env_size);
	gbl->cmds = NULL;
	gbl->aliases = NULL;
	register_cmds(gbl);
	setup_term(gbl);
	core(gbl);
}
