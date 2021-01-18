/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:35:31 by overetou          #+#    #+#             */
/*   Updated: 2021/01/18 16:46:17 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			invert_endian(char *s, UINT len)
{
	char			*new;
	UINT	i;

	new = secure_malloc(len);
	i = 0;
	while (i != len)
	{
		new[i] = s[len - i - 1];
		i++;
	}
	memcopy(s, new, len);
	free(new);
}

void			sha256_digest_init(t_sha_data *data, const char *input)
{
	data->initial_len = str_len(input);
	if (data->initial_len % 64 < 56)
		data->full_len = data->initial_len + 64 - (data->initial_len % 64);
	else
		data->full_len = data->initial_len + 128 - (data->initial_len % 64);
	data->full_msg = secure_malloc(data->full_len);
	memcopy((char*)(data->full_msg), input, data->initial_len);
	data->full_msg[data->initial_len] = 128;
	b_zero(data->full_msg + data->initial_len + 1,
	data->full_len - data->initial_len - 9);
	data->initial_len *= 8;
	memcopy((char*)(data->full_msg) + data->full_len - 8,
	(char*)(&(data->initial_len)), 8);
	invert_endian((char*)(data->full_msg + data->full_len - 8), 8);
	sha_init_hash(data);
	sha256_init_constants(data);
}

UINT			maj(UINT x, UINT y, UINT z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

void			loop_start(UINT *t, t_sha_data *d)
{
	UINT	t1;
	UINT	t2;

	while (*t != 16)
	{
		d->w[*t] = ((UINT*)(d->full_msg))[*t];
		invert_endian((char*)(d->w + (*t)), 4);
		(*t)++;
	}
	while (*t != 64)
	{
		d->w[*t] = sig1((d->w)[(*t) - 2]) + (d->w)[(*t) - 7] + sig0((d->w)[(*t) - 15]) + (d->w)[(*t) - 16];
		t++;
	}
	memcopy((char*)(d->a), (char*)(d->h), 8 * sizeof(int));
	*t = 0;
	while (*t != 64)
	{
		t1 = d->a[7] + eps1(d->a[4]) + ch(d->a[4], d->a[5], d->a[6]) + d->constants[*t] + ((UINT*)(d->w))[t];
		t2 = eps0(d->a[0]) + maj(d->a[0], d->a[1], d->a[2]);
		d->a[7] = d->a[6];
		d->a[6] = d->a[5];
		d->a[5] = d->a[4];
		d->a[4] = d->a[3] + t1;
		d->a[3] = d->a[2];
		d->a[2] = d->a[1];
		d->a[1] = d->a[0];
		d->a[0] = t1 + t2;
		(*t)++;
	}
}

unsigned char	*sha256_digest(const char *input)
{
	t_sha_data		data;
	UINT	t;

	sha256_digest_init(&data, input);
	data.bloc_pos = 0;
	while (data.bloc_pos != data.full_len)
	{
		t = 0;
		loop_start(&t, &data);
		data.bloc_pos += 64;
		data.h[0] += data.a[0];
		data.h[1] += data.a[1];
		data.h[2] += data.a[2];
		data.h[3] += data.a[3];
		data.h[4] += data.a[4];
		data.h[5] += data.a[5];
		data.h[6] += data.a[6];
		data.h[7] += data.a[7];
	}
	free(data.full_msg);
	t = 0;
	while (t != 8)
		invert_endian((char*)(data.h + t++), 4);
	return ((unsigned char*)(data.h));
}
