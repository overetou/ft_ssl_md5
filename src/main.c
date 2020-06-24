/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:48:45 by overetou          #+#    #+#             */
/*   Updated: 2020/06/24 18:43:47 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	putstr(const char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	write(1, s, i);
}

void	b_zero(void* s, int len)
{
	int i;

	i = 0;
	while (i != len)
	{
		((char*)s)[i] = 0;
		i++;
	}
}

char	*alloc_str(const char *content)
{
	int		i;
	char	*new;

	i = 0;
	while (content[i])
		i++;
	i = 0;
	new = malloc(i + 1);
	while (content[i])
	{
		new[i] = content[i];
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_master	m;

	m.still_reading_args = 1;
	m.command_given = 0;
	if (argc == 1)
	{
		putstr("usage: ft_ssl command [command opts] [command args]\n");
		m.still_reading_args = 0;
	}
	else if (argc == 2)
	{
		m.command_given = 1;

	}
	return (0);
}
