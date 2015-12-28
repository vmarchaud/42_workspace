/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 12:34:00 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/05 12:34:01 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_strfind(char *str1, char *str2)
{
	int i;
	int j;
	int size;

	size = 0;
	while (str2[size] != '\0')
		size++;
	if (size == 0)
		return (1);
	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		while (str1[i + j] == str2[j])
		{
			j++;
			if (j == size)
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}
