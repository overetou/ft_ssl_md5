#include "ft_ssl.h"

void	md5_execute_loaded(t_master *m)
{
	int	i;
	unsigned char	*md5sum;

	if (m->files_to_hash_nb)
	{
		// putstr("Inside file hash branch\n");
		i = 0;
		while (i != m->files_to_hash_nb)
		{
			exec_file_hash(m, m->files_to_hash[i]);
			i++;
		}
		free(m->files_to_hash);
		if (m->final_funcs_number)
		{
			// printf("Inside file hash branch, executing special tasks.\n final_funcs_number: %d\n", m->final_funcs_number);
			i = 0;
			while (i != m->final_funcs_number)
			{
				m->final_exec_funcs[i](m);
				i++;
			}
			free(m->final_exec_funcs);
		}
	}
	else
	{
		// putstr("No files to hash detected\n");
		if (m->final_funcs_number)
		{
			// printf("executing special tasks.\n final_funcs_number: %d\n", m->final_funcs_number);
			i = 0;
			while (i != m->final_funcs_number)
			{
				// printf("i = %d. p_exec adr = %p, current adr = %p\n", i, md5_p_exec, (m->final_exec_funcs)[i]);
				((m->final_exec_funcs)[i])(m);
				i++;
			}
			free(m->final_exec_funcs);
		}
		else
		{
			// putstr("Nothing given to hash. Reading from stdin.\n");
			load_stdin(m);
			md5sum = md5_digest(m->stdin_string);
			print_checksum(md5sum);
			free(md5sum);
			free(m->stdin_string);
			putstr("\n");
		}
	}
}
