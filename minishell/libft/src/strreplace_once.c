/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strreplace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:56:40 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/24 14:22:26 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strreplace_once(char *str, char *torepl, char *repl)
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
