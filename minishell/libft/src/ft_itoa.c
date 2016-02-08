/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:51:10 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/26 12:42:43 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_int(int n)
{
	if (n < 0)
		n = -n;
	if (n < 10)
		return (1);
	else
		return (ft_len_int(n / 10) + 1);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	len = neg ? ft_len_int(n) : ft_len_int(n) - 1;
	if ((str = ft_strnew(len + neg + 1)) == NULL)
		return (NULL);
	while (len >= 0)
	{
		str[len] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
