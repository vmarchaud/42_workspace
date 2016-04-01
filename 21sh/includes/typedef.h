/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:50:57 by vmarchau          #+#    #+#             */
/*   Updated: 2016/04/01 13:03:11 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct stat		t_stat;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_alias	t_alias;
typedef struct s_global	t_global;
typedef void			(t_builtin_cmd)(t_global*, int, char **);
typedef struct termios	t_termios;
typedef struct s_cursor	t_cursor;
typedef struct s_hist	t_hist;
typedef struct s_line	t_line;

#endif
