/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:39:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/13 15:15:03 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# define TRUE 1
# define FALSE 0

typedef struct		s_path
{
	char			*name;
	struct s_path	*next;
	struct s_filew	*files;
}					t_path;

typedef struct		s_filew
{
	char			*name;
	struct stat		*stat;
	__uint8_t		*type;
	struct s_filew	*next;
}					t_filew;

typedef struct		s_env
{
	t_path			*paths;

	int				show_dot;
	int				recursive;
	int				sort_time;
	int				reverse;
	int				format_out;
}					t_env;

int					parse(t_env *env, int size, char **args);
void				exit_clean(int error, char *msg, t_env *env);

void				ft_addpath(t_env *env, char *name);
void				ft_addfile(t_path *path, struct dirent *file);

void				compute_dir(t_env *env, t_path *path);
void				compute_dirs(t_env *env);
void				show_dir(t_env *env, t_path *path);
void				show_dirs(t_env *env);

int					is_hidden(char *name);

#endif
