#include "ft_ssl.h"

void	md5_execute_loaded(t_master *m)
{
	int	i;

	i = 0;
	while (i != m->final_funcs_number)
	{
		m->final_exec_funcs[i](m);
		i++;
	}
	free(m->final_exec_funcs);
}
