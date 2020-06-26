/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:07:38 by overetou          #+#    #+#             */
/*   Updated: 2020/06/26 17:13:30 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BOOL char
#define BUFF_MAX_SIZE 80

typedef struct	s_command
{
	char		*name;
	void		(*exec)(void* master);
}				t_command;

typedef struct	s_master
{
	char		**argv;
	char		buffer[BUFF_MAX_SIZE];
	char		*stdin_string;
	int			argc;
	int			buff_pos;
	int			buff_max;
	int			command_number;
	int			param_choice_number;
	t_command	*commands;
	t_command	*param_choice;
	BOOL		still_reading_args;
	BOOL		reverse_enabled;
	BOOL		quiet_enabled;
	BOOL		p_enabled;
	void		*(*param_exec)(void* master);
	void		(*final_exec_funcs)(struct s_master *m);
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
char	*get_command_name(t_master *m);
void	memcopy(char *dest, const char *src, int size);

void	test_exec(void* master);

#endif
