/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:06:11 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/14 14:40:30 by vmarchau         ###   ########.fr       */
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

char	*strjoins(char *first, char *second, char *third)
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
	t_env	*env;

	env = find_entry(gbl, "SHLVL");
	if (env == NULL || !env->value)
		gbl->env = put_entry(gbl, ft_strdup("SHLVL"), ft_strdup("1"));
	else
		env->value = ft_itoa(ft_atoi(env->value) + 1);
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

void	sighandler(int signum)
{
	ft_putstr("\n");
	(void)signum;
}
