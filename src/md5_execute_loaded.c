#include "ft_ssl.h"

void	md5_execute_loaded(t_master *m)
{
	int	i;
	unsigned char	*md5sum;

	if (m->final_funcs_number == 0 && m->files_to_hash == 0)
	{
		load_stdin(m);
		md5sum = md5_digest(m->stdin_string);
		print_checksum(md5sum);
		free(md5sum);
		free(m->stdin_string);
		putstr("\n");
	}
	else
	{
		i = 0;
		while (i != m->final_funcs_number)
		{
			m->final_exec_funcs[i](m);
			i++;
		}
		free(m->final_exec_funcs);
	}
	i = 0;
	while (i != m->files_to_hash_nb)
	{
		exec_file_hash(m, m->files_to_hash[i]);
		i++;
	}
}
