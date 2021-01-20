/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 09:18:01 by overetou          #+#    #+#             */
/*   Updated: 2021/01/18 15:37:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_digest_init(t_md5_data *d, const char *input)
{
	d->initial_len = str_len(input);
	d->h = secure_malloc(sizeof(int) * 4);
	if (64 - d->initial_len % 64 > 8)
		d->full_len = d->initial_len + 64 - (d->initial_len % 64);
	else
		d->full_len = d->initial_len + (64 - (d->initial_len + 8) % 64);
	md5_set_k((UINT*)(d->k));
	d->full_msg = secure_malloc(d->full_len);
	memcopy((char*)(d->full_msg), input, d->initial_len);
	d->full_msg[d->initial_len] = 128;
	b_zero(d->full_msg + d->initial_len + 1, d->full_len - d->initial_len - 9);
	d->initial_len *= 8;
	memcopy((char*)(d->full_msg) + d->full_len - 8,
	(char*)(&(d->initial_len)), 8);
	set_round_shift_table((unsigned char*)(d->round_shift_nb));
	md5_init_hash(d->h);
}

BOOL	try_arg(const char *s, t_master *m)
{
	int	i;

	i = 0;
	while (i != m->param_choice_number)
	{
		if (str_cmp(s, m->param_choice[i].name))
		{
			m->param_choice[i].exec(m);
			return (1);
		}
		i++;
	}
	return (0);
}

void	parse_args(t_master *m)
{
	m->files_to_hash = NULL;
	m->files_to_hash_nb = 0;
	if (m->still_reading_args)
	{
		m->arg_pos = 2;
		while (m->arg_pos != m->argc)
		{
			if (try_arg(m->argv[m->arg_pos], m) == 0)
				add_file_hash_task(m, m->argv[m->arg_pos]);
			(m->arg_pos)++;
		}
	}
}

void	md5_load_params_choice(t_master *m)
{
	m->param_choice_number = 4;
	m->param_choice = secure_malloc(4 * sizeof(t_command));
	command_add(0, m->param_choice, "-p", md5_p_exec);
	command_add(1, m->param_choice, "-q", q_exec);
	command_add(2, m->param_choice, "-r", r_exec);
	command_add(3, m->param_choice, "-s", md5_s_exec);
}

void	md5_exec(void *m)
{
	((t_master*)m)->digest = md5_digest;
	md5_load_params_choice(m);
	parse_args(m);
	md5_execute_loaded(m);
	free_commands(((t_master*)m)->param_choice,
					((t_master*)m)->param_choice_number);
}
