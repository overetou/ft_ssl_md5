/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_param_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:07:01 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:12:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha256_p_final_exec(t_master *m)
{
	unsigned char	*shasum;

	shasum = sha256_digest(m->stdin_string);
	putstr(m->stdin_string);
	if (m->stdin_string[str_len(m->stdin_string) - 1] != '\n')
		putstr("\n");
	disp_sum(shasum, 32);
	putstr("\n");
	ft_free(m->stdin_string);
	ft_free(shasum);
}

void	sha256_p_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		putstr("ft_ssl/sha256: -p argument"
		" given more than one time. (illegal action)\n");
	else
	{
		((t_master*)m)->p_enabled = 1;
		load_stdin(m);
		add_final_exec_func(m, sha256_p_final_exec);
	}
}

void	sha256_s_final_exec(t_master *m)
{
	unsigned char	*sha256_sum;

	sha256_sum = sha256_digest(m->direct_string);
	if (m->quiet_enabled)
		disp_sum(sha256_sum, 32);
	else
	{
		if (m->reverse_enabled)
		{
			disp_sum(sha256_sum, 32);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("SHA256 (\"");
			putstr(m->direct_string);
			putstr("\") = ");
			disp_sum(sha256_sum, 32);
		}
	}
	putstr("\n");
	ft_free(sha256_sum);
}

void	sha256_s_exec(void *m)
{
	if (((t_master*)m)->s_enabled)
		putstr("ft_ssl/sha256: -s argument"
		" given more than one time. (illegal action)\n");
	else
	{
		((t_master*)m)->s_enabled = 1;
		if (((t_master*)m)->arg_pos + 1 == ((t_master*)m)->argc)
			error_msg("ft_ssl/sha256: -s must be folowed by a"
			" string. Ex: hey / \" spaced words\"\n");
		(((t_master*)m)->arg_pos)++;
		((t_master*)m)->direct_string =
		((t_master*)m)->argv[((t_master*)m)->arg_pos];
		add_final_exec_func(m, sha256_s_final_exec);
	}
}
