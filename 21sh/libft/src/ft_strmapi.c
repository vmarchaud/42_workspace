/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:58:06 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/26 12:35:15 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	str = ft_strnew(len);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
