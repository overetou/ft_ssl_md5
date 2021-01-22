/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_param_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:39:22 by overetou          #+#    #+#             */
/*   Updated: 2021/01/22 16:39:46 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_p_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		putstr("ft_ssl/md5: -p argument given more than one time."
		" (illegal action)\n");
	else
	{
		((t_master*)m)->p_enabled = 1;
		load_stdin(m);
		add_final_exec_func(m, md5_p_final_exec);
	}
}

void	q_exec(void *m)
{
	if (((t_master*)m)->quiet_enabled)
		putstr("ft_ssl: -q argument given more than one time."
		" (illegal action)\n");
	else
		((t_master*)m)->quiet_enabled = 1;
}

void	r_exec(void *m)
{
	if (((t_master*)m)->reverse_enabled)
		putstr("ft_ssl: -r argument given more than one time."
		" (illegal action)\n");
	else
		((t_master*)m)->reverse_enabled = 1;
}

void	md5_s_exec(void *m)
{
	if (((t_master*)m)->s_enabled)
		putstr("ft_ssl/md5: -s argument given more than one time."
		" (illegal action)\n");
	else
	{
		((t_master*)m)->s_enabled = 1;
		if (((t_master*)m)->arg_pos + 1 == ((t_master*)m)->argc)
			error_msg("ft_ssl/md5: -s must be folowed by a string."
			" Ex: hey / \" spaced words\"\n");
		(((t_master*)m)->arg_pos)++;
		((t_master*)m)->direct_string =
		((t_master*)m)->argv[((t_master*)m)->arg_pos];
		add_final_exec_func(m, md5_s_final_exec);
	}
}

void	add_file_hash_task(t_master *m, char *file_name)
{
	(m->files_to_hash_nb)++;
	m->files_to_hash = secure_realloc(m->files_to_hash,
	(m->files_to_hash_nb - 1) * sizeof(char*),
	m->files_to_hash_nb * sizeof(char*));
	m->files_to_hash[m->files_to_hash_nb - 1] = file_name;
}
