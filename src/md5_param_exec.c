#include "ft_ssl.h"

void	md5_p_exec(void *m)
{
	if (((t_master*)m)->p_enabled)
		error_msg("ft_ssl/md5: -p argument given more than one time. (illegal action)\n");
	((t_master*)m)->p_enabled = 1;
	load_stdin(m);//This func alloc a string containing stdin and stores its address in the master struct.
	add_final_exec_func(m, md5_p_final_exec);// adds a func to the final exec list.
	//This one will process the stdin string and print the result while taking care of the r and q options.
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
	(void)m;
	putstr("md5 -s\n");
}
