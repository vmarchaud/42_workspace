/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:20:45 by vmarchau          #+#    #+#             */
/*   Updated: 2015/11/25 15:01:40 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str1, char *str2)
{
	int i;
	int j;
	int size;

	size = 0;
	while (str2[size] != '\0')
		size++;
	if (size == 0)
		return (str1);
	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		while (str1[i + j] == str2[j])
		{
			j++;
			if (j == size)
				return (str1 + i);
		}
		j = 0;
		i++;
	}
	return (0);
}
