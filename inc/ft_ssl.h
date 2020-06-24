/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:07:38 by overetou          #+#    #+#             */
/*   Updated: 2020/06/24 18:45:08 by overetou         ###   ########.fr       */
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
	BOOL		command_given;
	BOOL		still_reading_args;
	t_command	*commands;
	int			command_number;
}				t_master;

void	putstr(const char *s);
char	*alloc_str(const char *content);

#endif
