/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:46:08 by overetou          #+#    #+#             */
/*   Updated: 2021/01/29 16:05:28 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	str_len(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned int	left_rotate(unsigned int n, unsigned long times)
{
	return ((n << times % 32) | (n >> (32 - times % 32)));
}

void			load_stdin(t_master *m)
{
	int	i;

	m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	if (m->buff_max == 0)
		m->stdin_string = secure_malloc(1);
	else
		m->stdin_string = NULL;
	i = 0;
	while (m->buff_max)
	{
		if (m->buff_max == -1)
			error_msg("Error while reading on stdin.\n");
		m->stdin_string = secure_realloc(m->stdin_string, i,
		i + m->buff_max + 1);
		memcopy(m->stdin_string + i, m->buffer, m->buff_max);
		i += m->buff_max;
		m->buff_max = read(0, m->buffer, BUFF_MAX_SIZE);
	}
	m->stdin_string[i] = '\0';
}

long	file_len(int fd)
{
	long res = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return (res);
}
#include <string.h>
void			load_file(t_master *m, int fd, char **to_fill)
{
	unsigned int	i;
	long	flen;

	flen = file_len(fd);
	//printf("File len = %ld.\n", flen);
	m->buff_max = read(fd, m->buffer, BUFF_MAX_SIZE);
	if (m->buff_max)
		*to_fill = secure_malloc(flen + 1);
	else
		*to_fill = NULL;
	i = 0;
	//printf("Read %d bits.\n", m->buff_max);
	while (m->buff_max)
	{
		if (m->buff_max == -1)
			error_msg("Error while reading a file.\n");
		//printf("Copying %d bits from buffer to msg + %u\n", m->buff_max, i);
		memcopy((*to_fill) + i, m->buffer, m->buff_max);
		//puts("Still alive.");
		if (!memcmp(*to_fill, m->buffer, m->buff_max)) //puts("Copied correctly.");
		i += (unsigned int)(m->buff_max);
		//printf("i now equals %u.\n", i);
		m->buff_max = read(fd, m->buffer, BUFF_MAX_SIZE);
	}
	//puts("still alive");
	(*to_fill)[i] = '\0';
}
