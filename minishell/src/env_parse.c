/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:24:32 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 12:33:18 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_tab(t_env	*env, size_t size)
{
	char	**tab;
	size_t	i;
	t_env	*tmp;

	if ((tab = malloc(sizeof(char*) * size)) == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (i < size)
	{
		tab[i] = tmp->value;
		i++;
		tmp = tmp->next;
	}
	return (0);
}
