/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_param_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:07:01 by overetou          #+#    #+#             */
/*   Updated: 2020/07/03 09:30:07 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha256_p_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = sha256_digest(m->stdin_string);
	putstr(m->stdin_string);
	if (m->stdin_string[str_len(m->stdin_string) - 1] != '\n')
		putstr("\n");
	print_checksum(md5sum);
	putstr("\n");
	free(m->stdin_string);
	free(md5sum);
}

void	sha256_p_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		putstr("ft_ssl/sha256: -p argument given more than one time. (illegal action)\n");
	else
	{
		((t_master*)m)->p_enabled = 1;
		load_stdin(m);//This func alloc a string containing stdin and stores its address in the master struct.
		add_final_exec_func(m, sha256_p_final_exec);// adds a func to the final exec list.
	}
}

void	sha256_s_final_exec(t_master *m)
{
	unsigned char	*sha256_sum;

	sha256_sum = sha256_digest(m->direct_string);
	if (m->quiet_enabled)
		print_checksum(sha256_sum);
	else
	{
		if (m->reverse_enabled)
		{
			print_checksum(sha256_sum);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("SHA256 (\"");
			putstr(m->direct_string);
			putstr("\") = ");
			print_checksum(sha256_sum);
		}
	}
	putstr("\n");
	free(sha256_sum);
}

void	sha256_s_exec(void *m)
{
	if (((t_master*)m)->s_enabled)
		putstr("ft_ssl/sha256: -s argument given more than one time. (illegal action)\n");
	else
	{
		((t_master*)m)->s_enabled = 1;
		if (((t_master*)m)->arg_pos + 1 == ((t_master*)m)->argc)
			error_msg("ft_ssl/sha256: -s must be folowed by a string. Ex: hey / \" spaced words\"");
		(((t_master*)m)->arg_pos)++;
		((t_master*)m)->direct_string = ((t_master*)m)->argv[((t_master*)m)->arg_pos];
		add_final_exec_func(m, sha256_s_final_exec);// adds a func to the final exec list.
	}
}
