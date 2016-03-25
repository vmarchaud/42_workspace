/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:49:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/25 14:36:29 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>

void	core(t_global *gbl)
{
	char	*line;
	char	buff[21];
	int		i;

	while (42)
	{
		ft_putstr("$> ");
		line = ft_strnew(1);
		reset_cursor(gbl);
		i = 0;
		while (line[i] != 10 || line[i - 1] == 92)
		{
			ft_bzero(buff, 21);
			read(0, buff, 20);
			line = handle_input(gbl, buff, line);
			i = ft_strlen(line) - 1;
		}
		line[i] = 0;
		evaluate_line(gbl, line);
		gbl->history = reset_hist(gbl->history);
		if (ft_strlen(line) > 0)
			gbl->history = add_hist(gbl->history, new_hist(ft_strdup(line)));
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
	register_cmd(gbl, "aliaslst", &builtin_aliaslist);
	put_alias(gbl, ft_strdup("ls"), ft_strdup("ls -G"));
}

t_global	*init(char **env)
{
	t_global	*gbl;
	size_t		env_size;

	if ((gbl = malloc(sizeof(t_global))) == NULL)
		return (NULL);
	env_size = array_size(env);
	gbl->env_size = env_size;
	gbl->env = tab_to_env(env, env_size);
	update_shell_lvl(gbl);
	gbl->tabenv = env_to_tab(gbl->env, env_size);
	gbl->cmds = NULL;
	gbl->aliases = NULL;
	gbl->history = new_hist("");
	if ((gbl->cursor = malloc(sizeof(t_cursor))) == NULL)
		return (NULL);
	gbl->cursor->x = 0;
	gbl->cursor->y = 0;
	return (gbl);
}

int		main(int size, char **args, char **env)
{
	t_global	*gbl;

	(void)size;
	(void)args;
	if ((gbl = init(env)) == NULL)
		return (0);
	signal(SIGINT, SIG_IGN);
	register_cmds(gbl);
	setup_term(gbl);
	core(gbl);
}
