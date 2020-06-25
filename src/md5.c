/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 09:18:01 by overetou          #+#    #+#             */
/*   Updated: 2020/06/25 09:46:21 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

BOOL	md5_try_arg(const char *s, t_master *m)
{
	int	i;

	i = 0;
	while (i != m->md5_param_choice_number)
	{
		if (str_cmp(s, m->md5_param_choice[i].name))
		{
			m->commands[i].exec(m);
			return(1);
		}
		i++;
	}
	return(0);
}

void	md5_parse_args(t_master *m)
{
	int i;

	if (m->still_reading_args)
	{
		i = 2;
		while (i != m->argc)
		{
			if (md5_try_arg(m->argv[i], m))
				i++;
			else
				error_msg("md5: given arguments made no sense.");
		}
	}
}

void	md5_parse_args_on_stdin(t_master *m)
{
	int i;

	if (m->still_reading_args)
	{
		i = 2;
		while (i != m->argc)
		{
			if (md5_try_arg(m->argv[i], m))
				i++;
			else
				error_msg("md5: given arguments made no sense.");
		}
	}
}

void	md5_load_params_choice(t_master *m)
{
	m->md5_param_choice_number = 4;
	m->commands = secure_malloc(4 * sizeof(t_command));
	command_add(0, m->md5_param_choice, "-p", md5_p_exec);
	command_add(1, m->md5_param_choice, "-q", md5_q_exec);
	command_add(2, m->md5_param_choice, "-r", md5_r_exec);
	command_add(3, m->md5_param_choice, "-s", md5_s_exec);
}

void	md5_exec(void* m)
{
	md5_load_params_choice(m);
	md5_parse_args(m);
	// md5_parse_args_on_stdin(m);
	md5_execute_loaded(m);
	free_commands(((t_master*)m)->md5_param_choice,
					((t_master*)m)->md5_param_choice_number);
}
