/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_orientation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:01:14 by overetou          #+#    #+#             */
/*   Updated: 2021/01/22 16:15:44 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	command_add(const int command_index, t_command *commands,
					const char *command_name, void (*exec)(void*))
{
	commands[command_index].name = alloc_str(command_name);
	commands[command_index].exec = exec;
}

void	free_commands(t_command *commands, int command_number)
{
	int i;

	i = 0;
	while (i != command_number)
	{
		free(commands[i].name);
		i++;
	}
	free(commands);
}

void	load_commands(t_master *m)
{
	m->command_number = 2;
	m->commands = secure_malloc(2 * sizeof(t_command));
	command_add(0, m->commands, "md5", md5_exec);
	command_add(1, m->commands, "sha256", sha256_exec);
}

BOOL	try_to_exec_command(t_master *m, const char *try_name)
{
	int	i;

	load_commands(m);
	i = 0;
	while (i != m->command_number)
	{
		if (str_cmp(try_name, m->commands[i].name))
		{
			m->commands[i].exec(m);
			free_commands(m->commands, m->command_number);
			return (1);
		}
		i++;
	}
	free_commands(m->commands, m->command_number);
	return (0);
}
