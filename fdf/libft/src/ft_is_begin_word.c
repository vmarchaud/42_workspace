/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_begin_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:24:04 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/29 14:24:13 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_is_begin_word(char const *s, size_t index, char c)
{
    if (index == 0 && s[index] != c)
        return (1);
    if (s[index] != c && s[index - 1] == c)
        return (1);
    return (0);
}
