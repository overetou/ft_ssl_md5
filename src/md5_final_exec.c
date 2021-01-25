/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_final_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:23:39 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:12:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

void	md5_p_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->stdin_string);
	putstr(m->stdin_string);
	if (m->stdin_string[str_len(m->stdin_string) - 1] != '\n')
		putstr("\n");
	disp_sum(md5sum, 16);
	putstr("\n");
	ft_free(m->stdin_string);
	ft_free(md5sum);
}

void	md5_s_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->direct_string);
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
	ft_free(md5sum);
}

void	display_file_content_hash(t_master *m, char *f_content, char *f_name)
{
	unsigned char	*sum;

	sum = m->digest(f_content);
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
	ft_free(sum);
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
		load_file(m, fd, &file_content);
		close(fd);
		display_file_content_hash(m, file_content, file_name);
		ft_free(file_content);
	}
	putstr("\n");
}
