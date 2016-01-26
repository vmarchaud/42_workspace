/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:35:14 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/21 12:48:38 by vmarchau         ###   ########.fr       */
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
