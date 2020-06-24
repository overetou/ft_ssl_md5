#include "ft_ssl.h"

void	error_if_null(void *p, const char *err_msg)
{
	if (p)
		return ;
	error_msg(err_msg);
}

void	*secure_malloc(int	size)
{
	void	*new;

	new = malloc(size);
	error_if_null(new, "Allocation Failure");
	return (new);
}

void	error_msg(const char* msg)
{
	putstr(msg);
	exit(0);
}
