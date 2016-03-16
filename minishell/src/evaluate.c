/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:49:39 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/16 14:59:07 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_pattern(t_global *gbl, char *line)
{
	t_env	*entry;
	int		count;

	count = 0;
	if (ft_strchr(line, '~') && (entry = find_entry(gbl, "HOME")) != NULL)
		line = ft_replace_str(line, "~", entry->value);
	if (ft_strstr(line, " -") && (entry = find_entry(gbl, "OLDPWD")) != NULL &&
			*(ft_strchr(line, '-') + 1) == 0)
		line = ft_replace_str(line, "-", entry->value);
	while (ft_strchr(line, '$') != NULL && count < 5)
	{
		entry = gbl->env;
		while (entry && ft_strchr(line, '$'))
		{
			if (ft_strncmp(entry->key, ft_strchr(line, '$') + 1,
						ft_strlen(entry->key)) == 0)
				line = ft_replace_str(line, ft_strjoin("$", entry->key),
						entry->value);
			entry = entry->next;
		}
		count++;
	}
	return (line);
}

void	evaluate_line(t_global *gbl, char *line)
{
	t_cmd	*cmd;
	t_alias	*alias;
	char	**args;

	if (ft_strlen(line) > 0 && contains_char(line))
	{
		line = ft_replace_char(line, '\t', ' ');
		if ((alias = find_alias(gbl, line)) != NULL)
			line = alias->value;
		line = replace_pattern(gbl, line);
		args = ft_strsplit(line, ' ');
		if ((cmd = find_cmd(gbl, args[0])) != NULL)
			cmd->func(gbl, array_size(args), args);
		else
			execute_cmd(gbl, array_size(args), args, gbl->tabenv);
		ft_freetab(args);
	}
}
