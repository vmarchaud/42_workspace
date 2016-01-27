/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:57:23 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/27 13:01:39 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

void	print_file_type(mode_t st_mode)
{
	if ((S_ISFIFO(st_mode)))
		ft_putstr("p");
	else if ((S_ISCHR(st_mode)))
		ft_putstr("c");
	else if ((S_ISDIR(st_mode)))
		ft_putstr("d");
	else if ((S_ISBLK(st_mode)))
		ft_putstr("b");
	else if ((S_ISREG(st_mode)))
		ft_putstr("-");
	else if ((S_ISLNK(st_mode)))
		ft_putstr("l");
	else if ((S_ISSOCK(st_mode)))
		ft_putstr("s");
	else
		ft_putstr(" ");
}

void	print_file_rights(mode_t st_mode)
{
	char *ret; 
		
	ret = ft_strnew(10);
	ret[0] = ((st_mode & S_IRUSR) ? 'r' : '-');
	ret[1] = ((st_mode & S_IWUSR) ? 'w' : '-');
	ret[2] = ((st_mode & S_IXUSR) ? 'x' : '-');
	ret[3] = ((st_mode & S_IRGRP) ? 'r' : '-');
	ret[4] = ((st_mode & S_IWGRP) ? 'w' : '-');
	ret[5] = ((st_mode & S_IXGRP) ? 'x' : '-');
	ret[6] = ((st_mode & S_IROTH) ? 'r' : '-');
	ret[7] = ((st_mode & S_IWOTH) ? 'w' : '-');
	ret[8] = ((st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr(ret);
	ft_strdel(&ret);
}

void	print_file_owner(uid_t st_uid)
{
	struct passwd *pass;

	if ((pass = getpwuid(st_uid)) != NULL)
		ft_putstr(pass->pw_name);
	else
		ft_putstr(ft_itoa(st_uid));
}

void	print_file_group(gid_t gid)
{
	struct group *grp;

	if ((grp = getgrgid(gid)) != NULL)
		ft_putstr(grp->gr_name);
	else
		ft_putstr(ft_itoa(gid));
}

void	print_file_time(time_t mtime)
{
	char *tmp;
	char *ret;

	tmp = ft_strdup(ctime(&mtime));
	ret = ft_strsub(tmp, 4, 12);
	ft_putstr(ret);
	ft_strdel(&tmp);
	ft_strdel(&ret);
}
