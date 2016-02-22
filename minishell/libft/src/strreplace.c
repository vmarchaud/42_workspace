/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strreplace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:56:40 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/22 15:06:10 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strreplace(char *str, char *torepl, char *repl)
{
	char	*tmp;
	char	*i;
	char	*ret;

	i = ft_strstr(str, torepl);
	*i = '\0';
	ret = ft_strjoin(str, repl);
	tmp = ret;
	ret = ft_strjoin(ret, i + 1);
	free(tmp);
	return (ret);
}
