/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 09:18:01 by overetou          #+#    #+#             */
/*   Updated: 2020/07/02 18:15:00 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_digest_init(t_md5_data *data, const char *input)
{
	data->initial_len = str_len(input);
	md5_set_k((unsigned int*)(data->k));
	data->h = secure_malloc(sizeof(int) * 4);
	if (64 - data->initial_len % 64 > 8)
		data->full_len = data->initial_len + 64 - (data->initial_len % 64);
	else
		data->full_len = data->initial_len + (64 - (data->initial_len + 8) % 64);
	data->full_msg = secure_malloc(data->full_len);
	memcopy((char*)(data->full_msg), input, data->initial_len);
	data->full_msg[data->initial_len] = 128;
	b_zero(data->full_msg + data->initial_len + 1, data->full_len - data->initial_len - 9);
	data->initial_len *= 8;
	memcopy((char*)(data->full_msg) + data->full_len - 8, (char*)(&(data->initial_len)), 8);
	set_round_shift_table((unsigned char*)(data->round_shift_amount));
	md5_init_hash(data->h);
}

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
	m->files_to_hash = NULL;
	m->files_to_hash_nb = 0;
	if (m->still_reading_args)
	{
		m->arg_pos = 2;
		while (m->arg_pos != m->argc)
		{
			if (md5_try_arg(m->argv[m->arg_pos], m) == 0)
				md5_add_file_hash_task(m, m->argv[m->arg_pos]);
			(m->arg_pos)++;
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
