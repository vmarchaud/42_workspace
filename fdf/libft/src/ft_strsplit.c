/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:26:18 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/04 14:36:17 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static int			ft_getwordsnb(char const *s, char c)
{
    unsigned int	nb;
    size_t			i;
    
    i = 0;
    nb = 0;
    while (s && s[i])
    {
        while ((char)s[i] == c)
            i++;
        if (s[i] && (char)s[i] != c)
            nb++;
        while (s[i] && (char)s[i] != c)
            i++;
    }
    return (nb);
}

char				**ft_strsplit(char const *s, char c)
{
    char			*t;
    char			**splited;
    size_t			k;
    
    splited = (char**)malloc((ft_getwordsnb(s, c) + 1) * sizeof(char*));
    t = ft_strdup(s);
    k = 0;
    while (t && *t)
    {
        while (*t == c)
        {
            *t = 0;
            t++;
        }
        if (*t && *t != c)
        {
            splited[k] = t;
            k++;
        }
        while (*t && *t != c)
            t++;
    }
    splited[k] = 0;
    return (splited);
}