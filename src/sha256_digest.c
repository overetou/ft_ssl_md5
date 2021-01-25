/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:35:31 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:12:49 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			invert_endian(char *s, unsigned int len)
{
	char			*new;
	unsigned int	i;

	new = secure_malloc(len);
	i = 0;
	while (i != len)
	{
		new[i] = s[len - i - 1];
		i++;
	}
	memcopy(s, new, len);
	ft_free(new);
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

unsigned int	maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

unsigned char	*sha256_digest(const char *input)
{
	t_sha_data			data;
	unsigned int		t;

	sha256_digest_init(&data, input);
	data.bloc_pos = 0;
	while (data.bloc_pos != data.full_len)
	{
		loop_start(&data);
		second_loop(&data);
		change_h(&data);
	}
	ft_free(data.full_msg);
	t = 0;
	while (t != 8)
	{
		invert_endian((char*)(data.h + t), 4);
		t++;
	}
	return ((unsigned char*)(data.h));
}
