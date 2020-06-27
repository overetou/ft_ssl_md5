#include "ft_ssl.h"

int		str_len(const char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

void	load_stdin(t_master *m)
{
	int	i;

	m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	i = 0;
	while (m->buff_max)
	{
		if (m->buff_max == -1)
			error_msg("Error while reading on stdin.");
		m->stdin_string = secure_realloc(m->stdin_string, m->buff_max);
		memcopy(m->stdin_string + i, m->buffer, m->buff_max);
		i += BUFF_MAX_SIZE;
		m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	}
}
