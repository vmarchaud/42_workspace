/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:35:14 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 12:11:21 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_hidden(t_env *env, char *name)
{
	if (ft_strcmp(name, ".") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "..") == 0)
		return (TRUE);
	else if (*name == '.' && env->show_dot == FALSE)
		return (TRUE);
	else
		return (FALSE);
}

char		*ft_strjoins(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

size_t		count_block_used(t_path *path)
{
	size_t	count;
	t_filew	*tmp;

	tmp = path->files;
	count = 0;
	while (tmp)
	{
		count += tmp->stat->st_blocks;
		tmp = tmp->next;
	}
	return (count);
}

int			is_request_path(t_env *env, char *name)
{
	t_path *tmp;

	tmp = env->paths;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}
