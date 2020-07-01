/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 09:18:01 by overetou          #+#    #+#             */
/*   Updated: 2020/07/01 11:26:36 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

BOOL	md5_try_arg(const char *s, t_master *m)
{
	int	i;

	i = 0;
	while (i != m->param_choice_number)
	{
		if (str_cmp(s, m->param_choice[i].name))
		{
			m->param_choice[i].exec(m);
			return(1);
		}
		i++;
	}
	return(0);
}

void	md5_parse_args(t_master *m)
{
	if (m->still_reading_args)
	{
		m->arg_pos = 2;
		while (m->arg_pos != m->argc)
		{
			if (md5_try_arg(m->argv[m->arg_pos], m))
				(m->arg_pos)++;
			else
				error_msg("md5: given arguments made no sense.\n");
		}
	}
}

void	md5_load_params_choice(t_master *m)
{
	m->param_choice_number = 4;
	m->param_choice = secure_malloc(4 * sizeof(t_command));
	command_add(0, m->param_choice, "-p", md5_p_exec);
	command_add(1, m->param_choice, "-q", md5_q_exec);
	command_add(2, m->param_choice, "-r", md5_r_exec);
	command_add(3, m->param_choice, "-s", md5_s_exec);
}

void	md5_exec(void* m)
{
	md5_load_params_choice(m);
	md5_parse_args(m);
	md5_execute_loaded(m);
	free_commands(((t_master*)m)->param_choice,
					((t_master*)m)->param_choice_number);
}
