/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:44 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/15 15:06:00 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# define FALSE 0
# define TRUE 1

typedef void (builtin_cmd)(struct s_global, int, char **);

typedef struct	s_cmd
{
	char			*name;
	builtin_cmd		*func;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_env 
{
	char			*key;	
	char			*value;
	char			*old_value;
	struct s_env	*next;
}				t_env;

typedef	struct	s_global
{
	t_env			*env;
	size_t			env_size;
	t_cmd			*cmds;
	
}				t_global;

t_env				*new_entry(char *key, char *value);
void				clear_entry(t_env *env);
t_env				*del_env_entry(t_env *head, char *key);
t_env				*add_env_entry(t_env *head, t_env *entry);

char				**env_to_tab(t_env *env, size_t size);
t_env				*tab_to_env(char **tab, size_t size);

char				*assmbl_env(char *key, char *value);
t_env				*deassmbl_env(char *entry);

t_cmd				*new_cmd(char *name, builtin_cmd *funci);
t_cmd				*register_cmd(t_global *gbl, char *name, builtin_cmd *func);
t_cmd				*find_cmd(t_global *gbl, char *name);

void				builtin_env(t_global *gbl, int size, char **args);

int					array_size(void **array);

#endif
