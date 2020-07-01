#include "ft_ssl.h"
#include <fcntl.h>

void	md5_p_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->stdin_string);
	putstr(m->stdin_string);
	if (m->stdin_string[str_len(m->stdin_string) - 1] != '\n')
		putstr("\n");
	print_checksum(md5sum);
	putstr("\n");
	free(m->stdin_string);
	free(md5sum);
}

void	md5_s_final_exec(t_master *m)
{
	unsigned char	*md5sum;

	md5sum = md5_digest(m->direct_string);
	if (m->quiet_enabled)
		print_checksum(md5sum);
	else
	{
		if (m->reverse_enabled)
		{
			print_checksum(md5sum);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("MD5(\"");
			putstr(m->direct_string);
			putstr("\") ");
			print_checksum(md5sum);
		}
	}
	putstr("\n");
	free(md5sum);
}

void	exec_file_hash(t_master *m, char *file_name)
{
	char	*file_content;
	unsigned char	*md5sum;
	int fd;

	fd = open(file_name, O_RDONLY);
	load_file(m, fd, &file_content);
	close(fd);
	md5sum = md5_digest(file_content);
	if (m->quiet_enabled)
		print_checksum(md5sum);
	else
	{
		if (m->reverse_enabled)
		{
			print_checksum(md5sum);
			putstr(" \"");
			putstr(file_name);
			putstr("\"");
		}
		else
		{
			putstr("MD5(\"");
			putstr(file_name);
			putstr("\") ");
			print_checksum(md5sum);
		}
	}
	putstr("\n");
	free(file_content);
	free(md5sum);
}
