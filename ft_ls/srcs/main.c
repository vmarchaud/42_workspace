/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:34:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/29 15:36:12 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			exit_clean(int error, char *reason, t_env *env)
{
	(void)env;
	if (error)
		ft_putstr("ERROR : ");
	ft_putendl(reason);
	exit(0);
}

static void		sort_all(t_env *env)
{
	if (env->sort_time)
	{
		if (env->files && env->files->next)
			sort_file_by_time(env->files);
		if (env->paths && env->paths->next)
			sort_paths_by_time(env->paths);
	}
	else
	{
		if (env->files && env->files->next)
			sort_file_by_alpha(env->files);
		if (env->paths && env->paths->next)
			sort_paths_by_alpha(env->paths);
	}
	if (env->reverse)
	{
		if (env->files && env->files->next)
			sort_file_reverse(env->files);
		if (env->paths && env->paths->next)
			sort_paths_reverse(env->paths);
	}
}

static void		compute_all(t_env *env)
{

	t_path	*path;
	t_filew	*file;

	sort_all(env);
	file = env->files;
	while (file != NULL)
	{
		if (env->format_out)
			show_format_file(env, ft_newpath(file->path), file);
		else
			show_file(env, 0 , file);
		file = file->next;
	}
	if (env->files && env->files->next)
		ft_putstr("\n");
	path = env->paths;
	while (path != NULL)
	{
		compute_dir(env, path);
		path = path->next;
		if (path != NULL)
			ft_putstr("\n");
	}
}

int				main(int size, char **args)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit_clean(1, "cant malloc struct", env);
	env->recursive = FALSE;
	env->sort_time = FALSE;
	env->show_dot = FALSE;
	env->reverse = FALSE;
	env->format_out = FALSE;
	env->show_path_name = FALSE;
	env->paths = NULL;
	env->files = NULL;
	if (!parse(env, size, args))
		exit_clean(1, "parsing failed", env);
	compute_all(env);
	return (0);
}
