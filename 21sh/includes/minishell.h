/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:59:44 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/25 13:50:24 by vmarchau         ###   ########.fr       */
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
# define ISARROW_UP(in) (in[0] == 27 && in[1] == 91 && in[2] == 65 ? 1 : 0)
# define ISARROW_DOWN(in) (in[0] == 27 && in[1] == 91 && in[2] == 66 ? 1 : 0)
# define ISARROW_RIGHT(in) (in[0] == 27 && in[1] == 91 && in[2] == 67 ? 1 : 0)
# define ISARROW_LEFT(in) (in[0] == 27 && in[1] == 91 && in[2] == 68 ? 1 : 0)

#define ISARROW(in) \
	(ISARROW_UP(in) || ISARROW_DOWN(in) || ISARROW_RIGHT(in) || ISARROW_LEFT(in))

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
	t_hist			*history;
	t_termios		*term;
	t_cursor		*cursor;
	char			*line;
};

struct				s_cmd
{
	char			*name;
	t_builtin_cmd	*func;
	t_cmd			*next;
};

struct				s_cursor
{
	size_t			x;
	size_t			y;
};

struct				s_hist
{
	char			*cmd;
	t_hist			*next;
	t_hist			*prev;
};

void				evaluate_line(t_global *gbl, char *line);

void				setup_term(t_global *gbl);
void				reset_term(t_global *gbl);
char				*handle_input(t_global *gbl, char *input, char *line);

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
void				reset_cursor(t_global *gbl);

t_alias				*del_alias(t_alias *head, char *key);
void				clear_alias(t_alias *alias);
t_alias				*new_alias(char *key, char *value);
t_alias				*add_alias(t_alias *head, t_alias *entry);
t_alias				*find_alias(t_global *gbl, char *name);
t_alias				*put_alias(t_global *gbl, char *key, char *value);

t_hist				*new_hist(char *cmd);
t_hist				*add_hist(t_hist *head, t_hist *value);
t_hist				*find_hist(t_hist *head, char *cmd);
t_hist				*reset_hist(t_hist *head);
void				print_history(t_hist *head);

#endif
