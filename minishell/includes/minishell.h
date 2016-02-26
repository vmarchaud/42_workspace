/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:44 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/26 13:26:50 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# define FALSE 0
# define TRUE 1

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
	char			**tabenv;
	size_t			env_size;
	struct s_cmd	*cmds;
}				t_global;

typedef void (t_builtin_cmd)(t_global*, int, char **);

typedef struct	s_cmd
{
	char			*name;
	t_builtin_cmd	*func;
	struct s_cmd	*next;
}				t_cmd;


t_env				*new_entry(char *key, char *value);
void				clear_entry(t_env *env);
t_env				*del_env_entry(t_env *head, char *key);
t_env				*add_env_entry(t_env *head, t_env *entry);

char				**env_to_tab(t_env *env, size_t size);
t_env				*tab_to_env(char **tab, size_t size);
void				update_tabenv(t_global *gbl);

char				*assmbl_env(char *key, char *value);
t_env				*deassmbl_env(char *entry);
t_env				*find_entry(t_global *gbl, char *name);
t_env				*put_entry(t_global *gbl, char *key, char *name);

t_cmd				*new_cmd(char *name, t_builtin_cmd *func);
t_cmd				*register_cmd(t_global *gbl, char *name, t_builtin_cmd *f);
t_cmd				*find_cmd(t_global *gbl, char *name);

void				builtin_env(t_global *gbl, int size, char **args);
void				builtin_exit(t_global *gbl, int size, char **args);
void				builtin_setenv(t_global *gbl, int size, char **args);
void				builtin_unsetenv(t_global *gbl, int size, char **args);
void				builtin_cd(t_global *gbl, int size, char **args);
void				builtin_cd_here(t_global *gbl, char *path);

void				execute(t_global *gbl, char *path, int size, char **args);
int					execute_cmd(t_global *gbl, int size, char **args);

int					array_size(char **array);
char				*strjoins(char *first, char *second, char *third);
void				update_shell_lvl(t_global *gbl);
int					contains_char(char *str);
void				sighandler(int signum);

#endif
