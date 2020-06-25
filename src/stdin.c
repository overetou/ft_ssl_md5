#include "ft_ssl.h"

char	*get_command_name(t_master *m)
{
	char	*new;

	m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	if (m->buff_max == -1)
		error_msg("Error while reading on stdin.");
	while (m->buff_pos != m->buff_max && m->buffer[m->buff_pos] != ' '
	&& m->buffer[m->buff_pos] != '\t')
		(m->buff_pos)++;
	if (m->buff_pos == m->buff_max)
		error_msg("Command is invalid.\n");
	new = secure_malloc(m->buff_pos + 1);
	memcopy(new, m->buffer, m->buff_pos);
	new[m->buff_pos] = '\0';
	return (new);
}
