/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:19:44 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 14:20:12 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_count_word(char const *s, char c)
{
    size_t	i;
    size_t	count;
    
    count = 0;
    i = 0;
    while (s[i] != '\0')
    {
        while (s[i] == c)
            i++;
        if ((i == 1 && s[i] != c) || (s[i] != c && s[i - 1] == c))
            count++;
        i++;
    }
    return (count);
}