/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:38:49 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/30 13:32:29 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(char *str)
{
	int		i;
	int		neg;
	int		nbr;

	nbr = 0;
	i = 0;
	neg = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
						(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	if (neg)
		return (-nbr);
	return (nbr);
}
