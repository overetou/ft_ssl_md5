/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_final_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:23:39 by overetou          #+#    #+#             */
/*   Updated: 2021/01/29 16:00:33 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

void	md5_p_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	load_stdin(m);
	md5sum = md5_digest(m->stdin_string, m->msg_len);
	putstr(m->stdin_string);
	if (m->stdin_string[(m->msg_len) - 1] != '\n')
		putstr("\n");
	disp_sum(md5sum, 16);
	putstr("\n");
	free(m->stdin_string);
	free(md5sum);
}

void	md5_s_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->direct_string, str_len(m->direct_string));
	if (m->quiet_enabled)
		disp_sum(md5sum, 16);
	else
	{
		if (m->reverse_enabled)
		{
			disp_sum(md5sum, 16);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("MD5 (\"");
			putstr(m->direct_string);
			putstr("\") = ");
			disp_sum(md5sum, 16);
		}
	}
	putstr("\n");
	free(md5sum);
}

void	display_file_content_hash(t_master *m, char *f_content, char *f_name)
{
	unsigned char	*sum;

	sum = m->digest(f_content, m->msg_len);
	if (m->quiet_enabled)
		disp_sum(sum, (m->digest == md5_digest ? 16 : 32));
	else
	{
		if (m->reverse_enabled)
		{
			disp_sum(sum, (m->digest == md5_digest ? 16 : 32));
			putstr(" ");
			putstr(f_name);
		}
		else
		{
			if (m->digest == md5_digest)
				putstr("MD5 (");
			else
				putstr("SHA256 (");
			putstr(f_name);
			putstr(") = ");
			disp_sum(sum, (m->digest == md5_digest ? 16 : 32));
		}
	}
	free(sum);
}

void	exec_file_hash(t_master *m, char *file_name)
{
	char	*file_content;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		putstr("Could not open file: ");
		putstr(file_name);
	}
	else
	{
		//puts("file opened.");
		load_file(m, fd, &file_content);
		//puts("file loaded.");
		close(fd);
		display_file_content_hash(m, file_content, file_name);
		free(file_content);
	}
	putstr("\n");
}
