/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_disp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:31:30 by overetou          #+#    #+#             */
/*   Updated: 2020/07/02 14:49:04 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	uchar_print_hex(unsigned char c)
{
	char	buf[3];
	char	nbs[16];

	memcopy(nbs, "0123456789abcdef", 16);
	buf[0] = nbs[c / 16];
	if (c > 15)
		buf[1] = nbs[c - (c / 16) * 16];
	else
		buf[1] = nbs[c];
	buf[2] = '\0';
	putstr(buf);
}

void	print_checksum(unsigned char *s)
{
	int i;

	i = 0;
	while (i != 16)
	{
		uchar_print_hex(s[i]);
		i++;
	}
}
