/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_param_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:39:22 by overetou          #+#    #+#             */
/*   Updated: 2020/06/26 19:19:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_p_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		error_msg("ft_ssl/md5: -p argument given more than one time. (illegal action)\n");
	((t_master*)m)->p_enabled = 1;
	load_stdin(m);//This func alloc a string containing stdin and stores its address in the master struct.
	add_final_exec_func(m, md5_p_final_exec);// adds a func to the final exec list.
	//This one will process the stdin string.
}
void	md5_q_exec(void *m)
{
	if (((t_master*)m)->quiet_enabled)
		error_msg("ft_ssl/md5: -q argument given more than one time. (illegal action)\n");
	((t_master*)m)->quiet_enabled = 1;
}
void	md5_r_exec(void *m)
{
	if (((t_master*)m)->reverse_enabled)
		error_msg("ft_ssl/md5: -r argument given more than one time. (illegal action)\n");
	((t_master*)m)->reverse_enabled = 1;
}
void	md5_s_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		error_msg("ft_ssl/md5: -s argument given more than one time. (illegal action)\n");
	((t_master*)m)->p_enabled = 1;
	if (((t_master*)m)->arg_pos + 1 == ((t_master*)m)->argc)
		error_msg("ft_ssl/md5: -s must be folowed by a string. Ex: hey / \" spaced words\"");
	(((t_master*)m)->arg_pos)++;
	((t_master*)m)->direct_string = ((t_master*)m)->argv[((t_master*)m)->arg_pos];
	add_final_exec_func(m, md5_s_final_exec);// adds a func to the final exec list.
}
