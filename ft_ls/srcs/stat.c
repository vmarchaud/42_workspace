/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:57:23 by vmarchau          #+#    #+#             */
/*   Updated: 2016/01/26 14:14:38 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

char		*get_file_type(mode_t st_mode)
{
	if ((S_ISFIFO(st_mode)))
		return (ft_strdup("p"));
	else if ((S_ISCHR(st_mode)))
		return (ft_strdup("c"));
	else if ((S_ISDIR(st_mode)))
		return (ft_strdup("d"));
	else if ((S_ISBLK(st_mode)))
		return (ft_strdup("b"));
	else if ((S_ISREG(st_mode)))
		return (ft_strdup("-"));
	else if ((S_ISLNK(st_mode)))
		return (ft_strdup("l"));
	else if ((S_ISSOCK(st_mode)))
		return (ft_strdup("s"));
	else
		return (ft_strdup(" "));
}

char		*get_file_rights(mode_t st_mode)
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
	return (ret);
}

char		*get_file_owner(uid_t st_uid)
{
	struct passwd *pass;

	if ((pass = getpwuid(st_uid)) != NULL)
		return (ft_strdup(pass->pw_name));
	else
		return (ft_strdup(ft_itoa(st_uid)));
}

char		*get_file_group(gid_t gid)
{
	struct group *grp;

	if ((grp = getgrgid(gid)) != NULL)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_strdup(ft_itoa(gid)));
}

char		*get_file_time(time_t mtime)
{
	char *tmp;
	char *ret;

	tmp = ft_strdup(ctime(&mtime));
	ret = ft_strsub(tmp, 4, 12);
	free(tmp);
	return (ret);
}
