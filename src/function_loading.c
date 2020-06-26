#include "ft_ssl.h"

void	add_final_exec_func(t_master *m, void (*f)(t_master*))
{
	m->final_exec_funcs = realloc(m->final_exec_funcs, (m->final_funcs_number + 1) * sizeof(void*));
	m->final_exec_funcs[m->final_funcs_number] = (void*)f;
	(m->final_funcs_number)++;
}
