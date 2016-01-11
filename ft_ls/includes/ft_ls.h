/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:39:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/11 15:51:25 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# define TRUE 1
# define FALSE 0

typedef struct		s_path
{
	char			*path;
	DIR				*dir;
	struct s_path	*next;
	struct s_file	*files;
}					t_path;

typedef struct		s_file
{
	FILE			*file;
	struct s_file	*next;
}					s_file;

typedef struct		s_env
{
	// Path to show
	t_path			*paths;

	int				show_dot;
	int				recursive;
	int				sort_time;
	int				reverse;
	int				format_out;
}					t_env;

int			parse(t_env *env, int size, char **args);
void		exit_clean(int error, char *msg, t_env *env);
t_path		*ft_newpath(char *name);

# endif
