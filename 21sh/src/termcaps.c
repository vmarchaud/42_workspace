/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:17:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/18 14:41:44 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_term(t_global *gbl)
{
	t_env	*entry;

	entry = find_entry(gbl, "TERM");
	if (entry == NULL)
		return (ft_putstr_fd("Term type not found in env, no termcaps", 2));
	if (t_getent(NULL, &entry->value) != 1)
		return (ft_putstr_fd("Term not valid, no termcaps", 2));
	if (tcgetattr(0, gbl->term) != 0)
		return (ft_putstr_fd("Error while get attr of term, no termcaps", 2));
	gbl->term.c_lflag &= ~(ICANNON);
	gbl->term.c_lflag &= ~(ECHO);
	gbl->term.c_cc[VMIN] = 1;
	gbl->term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &gbl->term)) == -1)
		return (ft_putstr_fd("Error while set attr of term, not termcaps", 2));
}

void	reset_term(t_global *gbl)
{
	gbl->term.c_lflag = (ICANNON | ECHO);
	if (tcsetattr(0, TCSANOW, &gbl->term) == -1)
		return ;
}
