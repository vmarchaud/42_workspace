/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:39:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 14:18:52 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# define TRUE		1
# define FALSE		0

typedef struct		s_filew
{
	char			*name;
	struct stat		*stat;
	__uint8_t		*type;
	struct s_filew	*next;
}					t_filew;

typedef struct		s_path
{
	char			*name;
	struct s_path	*paths;
	struct s_filew	*files;
	struct stat		*stat;
	struct s_path	*next;
}					t_path;

typedef struct			s_env
{
	struct s_path	*paths;
	int				show_dot;
	int				recursive;
	int				sort_time;
	int				reverse;
	int				format_out;
}					t_env;

int					parse(t_env *env, int size, char **args);
void				exit_clean(int error, char *msg, t_env *env);

void				ft_addpath_env(t_env *env, char *name);
void				ft_addpath_path(t_path *path, char *name);
void				ft_addfile(t_path *path, struct dirent *file);

void				compute_dir(t_env *env, t_path *path);
void				compute_dirs(t_env *env);
void				explore_dir(t_env *env, t_path *path);

int					is_hidden(t_env *env, char *name);
char				*ft_strjoins(char *s1, char *s2, char *s3);
size_t				count_block_used(t_path *path);
int					is_request_path(t_env *env, char *name);

void				sort_file_by_alpha(t_path *path);
void				sort_file_reverse(t_path *path);
void				sort_paths_by_alpha(t_path *path);
void				sort_paths_reverse(t_path *path);
void				sort_paths_by_time(t_path *path);
void				sort_file_by_time(t_path *path);

void				print_file_type(mode_t st_mode);
void				print_file_rights(mode_t st_mode);
void				print_file_owner(uid_t st_uid);
void				print_file_group(gid_t gid);
void				print_file_time(time_t mtime);

#endif
