/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:49:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 14:02:14 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	evaluate_line(t_global *gbl, char *line)
{
	t_cmd	*cmd;
	t_alias	*alias;
	char	**args;

	if (ft_strlen(line) > 0 && contains_char(line))
	{
		line = ft_replace_char(line, '\t', ' ');
		if((alias = find_alias(gbl, line)) != NULL)
			line = alias->value;
		args = ft_strsplit(line, ' ');
		if ((cmd = find_cmd(gbl, args[0])) != NULL)
			cmd->func(gbl, array_size(args), args);
		else
			execute_cmd(gbl, array_size(args), args, gbl->tabenv);
		free(args);
	}
}

void	core(t_global *gbl)
{
	char	*line;
	int		i;
	char	**cmd;

	while ((ft_putstr("$> "), 42))
	{
		i = 0;
		get_next_line(0, &line);
		cmd = ft_strsplit(line, ';');
		while (cmd[i] != NULL)
			evaluate_line(gbl, cmd[i++]);
		free(cmd);
		free(line);
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
	gbl->aliases = add_alias(gbl->aliases, new_alias("ls", "ls -G"));
	register_cmds(gbl);
	core(gbl);
}
