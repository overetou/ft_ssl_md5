/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_disp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:31:30 by overetou          #+#    #+#             */
/*   Updated: 2021/01/20 16:51:28 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			md5_init_hash(unsigned int *h)
{
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
}

void			char_print_hex(unsigned char c)
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

void			disp_sum(unsigned char *s, int size)
{
	int i;

	i = 0;
	while (i != size)
	{
		char_print_hex(s[i]);
		i++;
	}
}

unsigned int	ch(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (~x & z));
}

unsigned int	maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
