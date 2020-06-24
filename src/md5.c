#include "ft_ssl.h"

void	md5_parse_args(t_master *m)
{
	int i;

	if (m->still_reading_args)
	{
		i = 2;
		while (i != m->argc)
		{
			if (md5_try_arg(m->argv[i], m))
				i++;
			else
				error_msg("md5: given arguments made no sense.");
		}
	}
}

void	md5_parse_args_on_stdin(t_master *m)
{
	int i;

	if (m->still_reading_args)
	{
		i = 2;
		while (i != m->argc)
		{
			if (md5_try_arg(m->argv[i], m))
				i++;
			else
				error_msg("md5: given arguments made no sense.");
		}
	}
}

void	md5_exec(void* m)
{
	md5_parse_args(m);
	md5_parse_args_on_stdin(m);
	md5_execute(m);
}
