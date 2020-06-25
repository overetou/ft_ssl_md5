/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:07:38 by overetou          #+#    #+#             */
/*   Updated: 2020/06/25 11:07:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	int			param_choice_number;
	t_command	*param_choice;
}				t_master;

void	putstr(const char *s);
char	*alloc_str(const char *content);
void	error_msg(const char* msg);
BOOL	str_cmp(const char *s1, const char *s2);
void	*secure_malloc(int	size);
void	command_add(const int command_index, t_command *commands,
const char *command_name, void (*exec)(void* master));
void	free_commands(t_command *commands, int command_number);
BOOL	try_to_exec_command(t_master *m, const char *try_name);
void	md5_exec(void* master);
void	md5_p_exec(void *m);
void	md5_q_exec(void *m);
void	md5_r_exec(void *m);
void	md5_s_exec(void *m);
void	md5_execute_loaded(t_master *m);

void	test_exec(void* master);

#endif
