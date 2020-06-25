#include "ft_ssl.h"

void	md5_p_exec(void *m)
{
	(void)m;
	putstr("md5 -p\n");
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
