/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strreplace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:56:40 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 15:44:54 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strreplace_once(char *str, char *pattern, char *repl)
{
	char	*tmp;
	char	*i;
	char	*ret;

	i = ft_strstr(str, pattern);
	if (ft_strcmp(str, pattern) != 0)
	{
		*i = 0;
		ret = ft_strjoin(str, repl);
		ret = ft_strjoin(ret, i + 1);
		free(tmp);
	}
	else
		ret = ft_strdup(repl);
	return (ret);
}
