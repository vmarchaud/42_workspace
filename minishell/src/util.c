/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:06:11 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/24 14:44:46 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		array_size(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*strjoins(char *first, char*second, char* third)
{
	char *ret;
	char *del;

	ret = ft_strjoin(first, second);
	del = ret;
	ret = ft_strjoin(ret, third);
	free(del);
	return (ret);
}

void	update_shell_lvl(t_global *gbl)
{
	t_env 	*env;
	char	*tmp;

	env = find_entry(gbl, "SHLVL");
	if (env == NULL)
		add_env_entry(gbl->env, new_entry("SHLVL", "1"));
	else
	{
		tmp = env->value;
		*tmp += 1;
		env->value = tmp;
	}
}

int		contains_char(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && str[i] != ' ')
			count++;
		i++;
	}
	return (count > 0 ? 1 : 0);
}
