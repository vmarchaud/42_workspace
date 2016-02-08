/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:38:49 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/01 13:00:51 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' ||
			c == '\n' ||
			c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r')
	{
		return (1);
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0') * sign;
		i++;
	}
	return (nb);
}
