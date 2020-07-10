/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_digest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 09:35:31 by overetou          #+#    #+#             */
/*   Updated: 2020/07/07 15:57:32 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			sha_init_hash(t_sha_data *data)
{
	data->h = secure_malloc(8 * sizeof(int));
	(data->h)[0] = 0x6a09e667;
	(data->h)[1] = 0xbb67ae85;
	(data->h)[2] = 0x3c6ef372;
	(data->h)[3] = 0xa54ff53a;
	(data->h)[4] = 0x510e527f;
	(data->h)[5] = 0x9b05688c;
	(data->h)[6] = 0x1f83d9ab;
	(data->h)[7] = 0x5be0cd19;
}

void			sha256_init_constants(t_sha_data *data)
{
	memcopy((char*)(data->constants), (char*)((unsigned int[64]){
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4,
	0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
	0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
	0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116,
	0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
	0xc67178f2}), 64 * sizeof(int));
}

void			sha256_digest_init(t_sha_data *data, const char *input)
{
	data->initial_len = str_len(input);
	if (data->initial_len % 64 < 56)
		data->full_len = data->initial_len + 64 - (data->initial_len % 64);
	else
		data->full_len = data->initial_len + 128 - (data->initial_len % 64);
	// printf("full len = %lu\n", data->full_len);
	data->full_msg = secure_malloc(data->full_len);
	memcopy((char*)(data->full_msg), input, data->initial_len);
	data->full_msg[data->initial_len] = 128;
	b_zero(data->full_msg + data->initial_len + 1, data->full_len - data->initial_len - 9);
	data->initial_len *= 8;
	memcopy((char*)(data->full_msg) + data->full_len - 8, (char*)(&(data->initial_len)), 8);
	sha_init_hash(data);
	sha256_init_constants(data);
}

void	print_deca(const unsigned char *s, unsigned int len)
{
    unsigned int i = 0;

	while (i != len)
	{
        printf(" %u", s[i]);
        i++;
	}
    puts("");
}

unsigned int	eps0(unsigned int x)
{
	return (right_rotate(x, 2) ^ right_rotate(x, 13) ^ right_rotate(x, 22));
}

unsigned int	eps1(unsigned int x)
{
	return (right_rotate(x, 6) ^ right_rotate(x, 11) ^ right_rotate(x, 25));
}

unsigned int	sig0(unsigned int x)
{
	return (right_rotate(x, 7) ^ right_rotate(x, 18) ^ (x >> 3));
}

unsigned int	sig1(unsigned int x)
{
	return (right_rotate(x, 17) ^ right_rotate(x, 19) ^ (x >> 10));
}

unsigned int	ch(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (~x & z));
}

unsigned int	maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

unsigned char	*sha256_digest(const char *input)
{
	t_sha_data		data;
	unsigned int	t1, t2;
	unsigned int	t;

	sha256_digest_init(&data, input);
	data.bloc_pos = 0;
	while (data.bloc_pos != data.full_len)
	{
		t = 0;
		while (t != 16)
		{
			data.w[t] = ((unsigned int*)(data.full_msg))[t];
			printf("w[%d] = %u\n", t, data.w[t]);
			t++;
		}
        exit(0);
		while (t != 64)
		{
			data.w[t] = sig1((data.w)[t - 2]) + (data.w)[t - 7] + sig0((data.w)[t - 15]) + (data.w)[t - 16];
			t++;
		}
		memcopy((char*)(data.a), (char*)(data.h), 8 * sizeof(int));
		t = 0;
		while(t != 64)
		{
			// printf("a = %u, b = %u, c = %u, d = %u, e = %u, f = %u, g = %u, h = %u\n", data.a[0], data.a[1], data.a[2], data.a[3], data.a[4], data.a[5], data.a[6], data.a[7]);
			printf("%u + %u (eps %u) + %u (ch %u + %u + %u) + %u + %u\n", data.a[7], eps1(data.a[4]), data.a[4], ch(data.a[4], data.a[5], data.a[6]), data.a[4], data.a[5], data.a[6], data.constants[t], *(((unsigned int*)(data.w)) + t));
			t1 = data.a[7] + eps1(data.a[4]) + ch(data.a[4], data.a[5], data.a[6]) + data.constants[t] + ((unsigned int*)(data.w))[t];
			t2 = eps0(data.a[0]) + maj(data.a[0], data.a[1], data.a[2]);
			// printf("t1 = %u\n", t1);
			// printf("t2 = %u (%u + %u), a = %u, b = %u, c = %u\n", t2, eps0(data.a[0]), maj(data.a[0], data.a[1], data.a[2]), data.a[0], data.a[1], data.a[2]);
			exit(0);
			data.a[7] = data.a[6];
			data.a[6] = data.a[5];
			data.a[5] = data.a[4];
			data.a[4] = data.a[3] + t1;
			data.a[3] = data.a[2];
			data.a[2] = data.a[1];
			data.a[1] = data.a[0];
			data.a[0] = t1 + t2;
			t++;
		}
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
	return ((unsigned char*)(data.h));
}
