/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:07:38 by overetou          #+#    #+#             */
/*   Updated: 2020/06/24 20:01:54 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <stdlib.h>

#define BOOL char

typedef struct	s_command
{
	char		*name;
	void		(*exec)(void* master);
}				t_command;

typedef struct	s_master
{
	int			argc;
	char		**argv;
	BOOL		command_given;
	BOOL		still_reading_args;
	t_command	*commands;
	int			command_number;
	void		*(*param_exec)(void* master);
}				t_master;

void	putstr(const char *s);
char	*alloc_str(const char *content);
void	error_msg(const char* msg);
BOOL	strcmp(const char *s1, const char *s2);
void	*secure_malloc(int	size);
BOOL	try_to_exec_command(t_master *m, const char *try_name);
void	md5_exec(void* master);

#endif
