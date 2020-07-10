#include "ft_ssl.h"

unsigned int		str_len(const char *s)
{
	unsigned int i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

unsigned int	left_rotate(unsigned int n, unsigned long times)
{
	return ((n << times % 32) | (n >> (32 - times % 32)));
}

unsigned int	right_rotate(unsigned int n, unsigned long times)
{
	return ((n >> times % 32) | (n << (32 - times % 32)));
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
		m->stdin_string = secure_realloc(m->stdin_string, i + m->buff_max + 1);
		memcopy(m->stdin_string + i, m->buffer, m->buff_max);
		i += m->buff_max;
		m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	}
	m->stdin_string[i] = '\0';
}

void	load_file(t_master *m, int fd, char **to_fill)
{
	int	i;

	m->buff_max = read(fd, m->buffer, BUFF_MAX_SIZE);
	i = 0;
	*to_fill = NULL;
	while (m->buff_max)
	{
		if (m->buff_max == -1)
			error_msg("Error while reading a file.");
		*to_fill = secure_realloc(*to_fill, i + m->buff_max + 1);
		memcopy(*to_fill + i, m->buffer, m->buff_max);
		i += m->buff_max;
		m->buff_max = read(fd, m->buffer, BUFF_MAX_SIZE);
	}
	(*to_fill)[i] = '\0';
}
