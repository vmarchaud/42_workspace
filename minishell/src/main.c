/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:49:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/22 16:28:25 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	core(t_global *gbl)
{
	char	*line;
	char	**args;
	t_cmd	*cmd;

	while ((ft_putstr("$> "), 42))
	{
		get_next_line(0, &line);
		if (ft_strlen(line) > 0)
		{
			args = ft_strsplit(line, ' ');
			if ((cmd = find_cmd(gbl, args[0])) != NULL)
				cmd->func(gbl, array_size(args), args);
			else
				execute_cmd(gbl, array_size(args), args);
			free(line);
			free(args);
		}
	}
}

void	register_cmds(t_global *gbl)
{
	register_cmd(gbl, "env", &builtin_env);
	register_cmd(gbl, "exit", &builtin_exit);
	register_cmd(gbl, "setenv", &builtin_setenv);
	register_cmd(gbl, "unsetenv", &builtin_unsetenv);
	register_cmd(gbl, "cd", &builtin_cd);
}

int		main(int size, char **args, char **env)
{
	t_global	*gbl;
	size_t		env_size;

	(void)size;
	(void)args;
	if ((gbl = malloc(sizeof(t_global))) == NULL)
		return (0);
	env_size = array_size(env);
	gbl->env_size = env_size;
	gbl->env = tab_to_env(env, env_size);
	update_shell_lvl(gbl);
	gbl->tabenv = env_to_tab(gbl->env, env_size);
	gbl->cmds = NULL;
	register_cmds(gbl);
	core(gbl);
}
