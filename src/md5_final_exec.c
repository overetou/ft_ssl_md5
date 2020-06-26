#include "ft_ssl.h"

void	md5_p_final_exec(t_master *m)
{
	int	md5sum;

	md5sum = md5_digest(m->stdin_string);
	putstr(m->stdin_string);
	putstr("\n");
	print_sum(md5sum);
	putstr("\n");
}

void	md5_s_final_exec(t_master *m)
{
	int	md5sum;

	md5sum = md5_digest(m->direct_string);
	if (m->quiet_enabled)
		print_sum(md5sum);
	else
	{
		if (m->reverse_enabled)
		{
			print_sum(md5sum);
			putstr(" \"");
			putstr(m->direct_string);
			putstr("\"");
		}
		else
		{
			putstr("MD(\"");
			putstr(m->direct_string);
			putstr("\" ");
			print_sum(md5sum);
		}
	}
	putstr("\n");
}
