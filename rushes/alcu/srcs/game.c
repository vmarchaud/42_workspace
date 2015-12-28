/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 10:10:02 by vmarchau          #+#    #+#             */
/*   Updated: 2015/12/21 15:40:15 by mbouhier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

void		remove_matches(t_env *env, int nbr)
{
	int i;

	i = 0;
	if (ft_strlen(env->map[env->len - 1]) - nbr == 0)
		env->len--;
	else
		env->map[env->len - 1][ft_strlen(env->map[env->len - 1]) - nbr] = 0;
}

int			count_matches(t_env *env)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < env->len)
	{
		count += ft_strlen(env->map[i]);
		i++;
	}
	return (count);
}

void		compute_ia_move(t_env *env)
{
	int i;
	int diff;
	int matches;

	i = 0;
	matches = count_matches(env);
	while (i * 4 + 1 < matches)
		i++;
	if (i > 0)
		i--;
	diff = matches - (i * 4 + 1);
	if (diff > 3)
		diff = 3;
	else if (diff < 1 || diff >= ft_strlen(env->map[env->len - 1]))
		diff = 1;
	remove_matches(env, diff);
}

int			make_all_move(t_env *env, int nbr)
{
	env->turn = 1;
	remove_matches(env, nbr);
	if (env->len == 0)
		return (1);
	ft_putstr("\nBoard after your move :\n");
	show_map(env);
	env->turn = 0;
	ft_putstr("\nBoard after IA move :\n");
	compute_ia_move(env);
	if (env->len == 0)
		return (1);
	show_map(env);
	return (0);
}

int			play(t_env *env)
{
	char	*ret;
	int		nbr;
	int		gnl_ret;

	if ((ret = ft_strnew(100)) == NULL)
		return (0);
	ft_putendl("\nHow many matches you want to remove (between 1 and 3) ?");
	while (get_next_line(1, &ret) < 1)
		;
	nbr = ft_atoi(ret);
	if (nbr < 1 || nbr > 3 || !ft_isnumeric(ret) ||
		nbr > ft_strlen(env->map[env->len - 1]))
	{
		free(ret);
		return (play(env));
	}
	if (make_all_move(env, nbr))
		return (1);
	return (play(env));
}
