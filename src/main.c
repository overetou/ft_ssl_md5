/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:48:45 by overetou          #+#    #+#             */
/*   Updated: 2021/01/29 16:04:02 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	putstr(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	b_zero(void *s, int len)
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
	new = secure_malloc(i + 1);
	memcopy(new, content, i);
	new[i] = '\0';
	return (new);
}

BOOL	str_cmp(const char *s1, const char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] == s2[i]);
}

int		main(int argc, char **argv)
{
	t_master	m;

	if (argc <= 1)
		putstr("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		m.argc = argc;
		m.argv = argv;
		m.still_reading_args = 1;
		m.buff_pos = 0;
		m.reverse_enabled = 0;
		m.quiet_enabled = 0;
		m.p_enabled = 0;
		m.s_enabled = 0;
		m.final_funcs_number = 0;
		m.final_exec_funcs = NULL;
		if (try_to_exec_command(&m, argv[1]) == 0)
		{
			error_msg("Given command could not be processed.\n"
			"usage: ft_ssl command [command opts] [command args]\n");
		}
	}
	return (0);
}
