/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:44 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/21 15:39:33 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "typedef.h"
# include "termios.h"
# include "term.h"
# include <sys/stat.h>
# include <sys/types.h>
# define FALSE 0
# define TRUE 1
# undef tab
# define ISKEYUP(in) (in[0] == 65 && in[1] == 91 && in[2] == 27 ? 1 : 0)
# define ISKEYDOWN(in) (in[0] == 66 && in[1] == 91 && in[2] == 27 ? 1 : 0)
# define ISKEYRIGHT(in) (in[0] == 67 && in[1] == 91 && in[2] == 27 ? 1 : 0)
# define ISKEYLEFT(in) (in[0] == 68 && in[1] == 91 && in[2] == 27 ? 1 : 0)

struct				s_env
{
	char			*key;
	char			*value;
	char			*old_value;
	t_env			*next;
};

struct				s_alias
{
	char			*key;
	char			*value;
	t_alias			*next;
};

struct				s_global
{
	t_env			*env;
	t_alias			*aliases;
	char			**tabenv;
	size_t			env_size;
	t_cmd			*cmds;
	t_termios		*term;
};

struct				s_cmd
{
	char			*name;
	t_builtin_cmd	*func;
	t_cmd			*next;
};

void				evaluate_line(t_global *gbl, char *line);

void				setup_term(t_global *gbl);
void				reset_term(t_global *gbl);
char				*handle_input(char *input, char *line);

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
void				builtin_alias(t_global *gbl, int size, char **args);
void				builtin_unalias(t_global *gbl, int size, char **args);
void				builtin_aliaslist(t_global *gbl, int size, char **args);

void				execute(t_global *gbl, char *path, char **args, char **tab);
int					execute_cmd(t_global *gbl, int size,
						char **args, char **tab);

int					array_size(char **array);
char				*strjoins(char *first, char *second, char *third);
void				update_shell_lvl(t_global *gbl);
int					contains_char(char *str);
void				sighandler(int signum);

t_alias				*del_alias(t_alias *head, char *key);
void				clear_alias(t_alias *alias);
t_alias				*new_alias(char *key, char *value);
t_alias				*add_alias(t_alias *head, t_alias *entry);
t_alias				*find_alias(t_global *gbl, char *name);
t_alias				*put_alias(t_global *gbl, char *key, char *value);

#endif
