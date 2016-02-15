/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:44 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 12:33:11 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# define FALSE 0
# define TRUE 1


typedef struct	s_env {
	
	char			*value;
	char			*old_value;
	struct s_env	*next;
}				t_env;

typedef	struct	s_global {
	t_env		*env;
	size_t		env_size;

}				t_global;

#endif
