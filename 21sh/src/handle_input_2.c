/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:09:37 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/30 13:25:32 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_home_end(t_global *gbl, char *input, char *line)
{
	if (IS_HOME(input))
		goto_start(gbl);
	else if (IS_END(input))
		goto_end(gbl, line);
	return (line);
}
