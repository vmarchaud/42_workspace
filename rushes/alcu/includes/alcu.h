/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 12:11:20 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/21 14:20:00 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H
# include <libft.h>

typedef struct	s_env
{
	char	**map;
	char	turn;
	int		len;
}				t_env;

int				parse(int const fd, t_env *env);
void			show_map(t_env *env);
char			*setup_line(int nb);
int				setup_map(t_env *env, t_list *tmp);
void			compute_ia_move(t_env *env);
void			remove_matches(t_env *env, int nbr);
int				count_matches(t_env *env);
int				make_all_move(t_env *env, int nbr);
int				play(t_env *env);

#endif
