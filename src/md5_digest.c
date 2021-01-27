/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_digest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:34 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:35:37 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			set_round_shift_table(unsigned char *r)
{
	memcopy((char*)(r), (char[64]){7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14,
	20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
	15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}, 64);
}

void			md5_set_k(unsigned int *to_set)
{
	memcopy((char*)to_set, (char*)((unsigned int[64]){
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391}), 64 * sizeof(int));
}

void			set_f_and_g(t_md5_data *data)
{
	if (data->word_pos < 16)
	{
		data->f = (data->b & data->c) | ((~data->b) & data->d);
		data->g = data->word_pos;
	}
	else if (data->word_pos < 32)
	{
		data->f = (data->b & data->d) | (data->c & (~(data->d)));
		data->g = (5 * data->word_pos + 1) % 16;
	}
	else if (data->word_pos < 48)
	{
		data->f = data->b ^ data->c ^ data->d;
		data->g = (3 * data->word_pos + 5) % 16;
	}
	else
	{
		data->f = data->c ^ (data->b | (~data->d));
		data->g = (7 * data->word_pos) % 16;
	}
}

void			update_h(t_md5_data *data)
{
	(data->h)[0] += data->a;
	(data->h)[1] += data->b;
	(data->h)[2] += data->c;
	(data->h)[3] += data->d;
}

unsigned char	*md5_digest(const char *input)
{
	t_md5_data	d;

	md5_digest_init(&d, input);
	d.bloc_pos = 0;
	while (d.bloc_pos != d.full_len)
	{
		d.w = d.full_msg + d.bloc_pos;
		d.word_pos = 0;
		memcopy((char*)(&(d.a)), (char*)(d.h), 4 * sizeof(int));
		while (d.word_pos != 64)
		{
			set_f_and_g(&d);
			d.temp = d.d;
			d.d = d.c;
			d.c = d.b;
			d.b = d.b + left_rotate(d.a + d.f + (d.k)[d.word_pos] +
			*(((unsigned int*)(d.w)) + d.g), (d.round_shift_nb)[d.word_pos]);
			d.a = d.temp;
			(d.word_pos)++;
		}
		update_h(&d);
		d.bloc_pos += 64;
	}
	free(d.full_msg);
	return ((unsigned char*)(d.h));
}
