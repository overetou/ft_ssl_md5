/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:35:31 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:35:37 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			compute_w(unsigned int *bloc, unsigned int *w)
{
	int j;

	j = 0;
	while (j != 16)
	{
		w[j] = bloc[j];
		invert_endian((unsigned char*)(w + j), 4);
		j++;
	}
	while (j != 64)
	{
		w[j] = sig1(w[j - 2]) + w[j - 7] + sig0(w[j - 15]) + w[j - 16];
		j++;
	}
}

void			compress(unsigned int *letters,
unsigned int *bloc, t_sha_data *data)
{
	int				j;
	unsigned int	w[64];
	unsigned int	t1;
	unsigned int	t2;

	j = 0;
	compute_w(bloc, w);
	while (j != 64)
	{
		t1 = letters[7] + eps1(letters[4]) + ch(letters[4], letters[5],
		letters[6]) + data->konstants[j] + w[j];
		t2 = eps0(letters[0]) + maj(letters[0], letters[1], letters[2]);
		letters[7] = letters[6];
		letters[6] = letters[5];
		letters[5] = letters[4];
		letters[4] = letters[3] + t1;
		letters[3] = letters[2];
		letters[2] = letters[1];
		letters[1] = letters[0];
		letters[0] = t1 + t2;
		j++;
	}
}

void			operate_on_block(t_sha_data *data, unsigned int *block)
{
	unsigned int	letters[8];

	letters[0] = data->h[0];
	letters[1] = data->h[1];
	letters[2] = data->h[2];
	letters[3] = data->h[3];
	letters[4] = data->h[4];
	letters[5] = data->h[5];
	letters[6] = data->h[6];
	letters[7] = data->h[7];
	compress(letters, block, data);
	data->h[0] += letters[0];
	data->h[1] += letters[1];
	data->h[2] += letters[2];
	data->h[3] += letters[3];
	data->h[4] += letters[4];
	data->h[5] += letters[5];
	data->h[6] += letters[6];
	data->h[7] += letters[7];
}

void			iterate_on_blocks(t_sha_data *d)
{
	unsigned long long	pos;

	pos = 0;
	while (pos != d->full_len)
	{
		operate_on_block(d, (unsigned int*)(d->blocks + pos));
		pos += 64;
	}
}

unsigned char	*sha256_digest(const char *msg, unsigned long long msg_len)
{
	t_sha_data	d;
	int			i;

	d.msg_len = msg_len;
	load_hashable_blocks((unsigned char*)msg, &d);
	sha_init_hash(&d);
	sha256_init_constants(d.konstants);
	iterate_on_blocks(&d);
	free(d.blocks);
	i = 0;
	while (i != 8)
	{
		invert_endian((unsigned char*)(d.h + i), sizeof(int));
		i++;
	}
	return ((unsigned char*)(d.h));
}
