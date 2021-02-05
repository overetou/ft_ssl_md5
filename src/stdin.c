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
#include <sys/types.h>
#include <sys/stat.h>

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
	long	i;

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
	m->msg_len = str_len(m->stdin_string);
}

void			load_file(t_master *m, int fd, char **to_fill)
{
	struct stat statbuf;
	ssize_t	buffered;
	char 		*temp;
	off_t		left;
	
	fstat(fd, &statbuf);
	m->msg_len = (unsigned long long)(statbuf.st_size);
	*to_fill = secure_malloc(statbuf.st_size + 1);
	temp = *to_fill;
	left = statbuf.st_size;
	while ((buffered = read(fd, temp, BUFF_MAX_SIZE)) > 0)
	{
		temp += buffered;
		left -= buffered;
		//printf("Left to read: %ld\n", left);
	}
	if (buffered < 0)
	{
		putstr("Error while reading file.");
		exit(0);
	}
}
