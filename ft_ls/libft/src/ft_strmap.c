/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:46:11 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/27 11:57:50 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	str = ft_strnew(len);
	while (i < len)
	{
		str[i] = f(s[i]);
		i++;
	}
	return (str);
}
