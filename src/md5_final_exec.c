#include "ft_ssl.h"
#include <fcntl.h>

void	md5_p_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->stdin_string);
	putstr(m->stdin_string);
	if (m->stdin_string[str_len(m->stdin_string) - 1] != '\n')
		putstr("\n");
	print_checksum(md5sum, 16);
	putstr("\n");
	free(m->stdin_string);
	free(md5sum);
}

void	md5_s_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->direct_string);
	if (m->quiet_enabled)
		print_checksum(md5sum, 16);
	else
	{
		if (m->reverse_enabled)
		{
			print_checksum(md5sum, 16);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("MD5 (\"");
			putstr(m->direct_string);
			putstr("\") = ");
			print_checksum(md5sum, 16);
		}
	}
	putstr("\n");
	free(md5sum);
}

void	display_file_content_hash(t_master *m, char *file_content, char *file_name)
{
	unsigned char	*sum;

	sum = m->digest(file_content);
	if (m->quiet_enabled)
		print_checksum(sum, (m->digest == md5_digest ? 16 : 32));
	else
	{
		if (m->reverse_enabled)
		{
			print_checksum(sum, (m->digest == md5_digest ? 16 : 32));
			putstr(" ");
			putstr(file_name);
		}
		else
		{
			putstr("MD5 (");
			putstr(file_name);
			putstr(") = ");
			print_checksum(sum, (m->digest == md5_digest ? 16 : 32));
		}
	}
	free(sum);
}

void	exec_file_hash(t_master *m, char *file_name)
{
	char			*file_content;
	int 			fd;

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
		free(file_content);
	}
	putstr("\n");
}
