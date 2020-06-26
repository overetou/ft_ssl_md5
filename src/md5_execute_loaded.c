#include "ft_ssl.h"

void	md5_execute_loaded(t_master *m)
{
	putstr("md5: execution\n");
	free(m->final_exec_funcs);
}
