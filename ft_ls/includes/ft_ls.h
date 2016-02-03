/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:39:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/02/03 14:21:49 by vmarchau         ###   ########.fr       */
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

typedef struct stat	t_stat;

typedef struct		s_filew
{
	char			*name;
	t_stat			*stat;
	__uint8_t		*type;
	char			*path;
	struct s_filew	*next;
}					t_filew;

typedef struct		s_path
{
	char			*name;
	struct s_path	*paths;
	struct s_filew	*files;
	t_stat			*stat;
	struct s_path	*next;
}					t_path;

typedef struct		s_env
{
	struct s_path	*paths;
	struct s_filew	*files;
	int				show_dot;
	int				recursive;
	int				sort_time;
	int				reverse;
	int				format_out;
	int				show_path_name;
}					t_env;

int					parse(t_env *env, int size, char **args);
void				exit_clean(int error, char *msg, t_env *env);

void				ft_addpath_env(t_env *env, char *name);
void				ft_addpath_path(t_path *path, char *name);
void				ft_addfile(t_path *path, struct dirent *file);
t_filew				*ft_newfile(struct dirent *dirent);
t_path				*ft_newpath(char *name);

void				compute_dir(t_env *env, t_path *path);
void				explore_dir(t_env *env, t_path *path);

int					is_hidden(t_env *env, char *name);
char				*ft_strjoins(char *s1, char *s2, char *s3);
size_t				count_block_used(t_env *env, t_path *path);
int					is_request_path(t_env *env, char *name);
char				*get_real_path(char *path);

void				sort_file_by_alpha(t_filew *file);
t_filew				*sort_file_reverse(t_filew *file);
void				sort_paths_by_alpha(t_path *path);
void				sort_paths_reverse(t_path *path);
void				sort_paths_by_time(t_path *path);
void				sort_file_by_time(t_filew *file);

void				print_file_type(mode_t st_mode);
void				print_file_rights(mode_t st_mode);
void				print_file_owner(uid_t st_uid);
void				print_file_group(gid_t gid);
void				print_file_time(time_t mtime);
void				print_link(t_path *path, t_filew *file);
void				print_major_minor(dev_t st_rev);

void				show_format_path(t_env *env, t_path *path);
void				show_path(t_env *env, t_path *path);
void				show_format_file(t_env *env, t_path *path, t_filew *file);
void				show_file(t_env *env, t_path *path, t_filew *file);

void				free_files(t_filew *head);
void				free_paths(t_path *head);

#endif
