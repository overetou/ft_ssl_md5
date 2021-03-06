/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 08:44:52 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:35:37 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			sha256_load_params_choice(t_master *m)
{
	m->param_choice_number = 4;
	m->param_choice = secure_malloc(4 * sizeof(t_command));
	command_add(0, m->param_choice, "-p", sha256_p_exec);
	command_add(1, m->param_choice, "-q", q_exec);
	command_add(2, m->param_choice, "-r", r_exec);
	command_add(3, m->param_choice, "-s", sha256_s_exec);
}

void			sha256_execute_loaded(t_master *m)
{
	unsigned char	*sha256_sum;

	if (m->files_to_hash_nb)
		exec_files_hash_and_funcs(m);
	else
	{
		if (m->final_funcs_number)
			exec_final_funcs(m);
		else
		{
			load_stdin(m);
			sha256_sum = sha256_digest(m->stdin_string, m->msg_len);
			disp_sum(sha256_sum, 32);
			free(sha256_sum);
			free(m->stdin_string);
			putstr("\n");
		}
	}
}

void			sha256_exec(void *m)
{
	((t_master*)m)->digest = sha256_digest;
	sha256_load_params_choice(m);
	parse_args(m);
	sha256_execute_loaded(m);
	free_commands(((t_master*)m)->param_choice,
					((t_master*)m)->param_choice_number);
}

unsigned int	right_rotate(unsigned int x, unsigned int n)
{
	return (x >> n) | (x << ((sizeof(x) * 8) - n));
}

unsigned int	sig0(unsigned int x)
{
	return (right_rotate(x, 7) ^ right_rotate(x, 18) ^ (x >> 3));
}
