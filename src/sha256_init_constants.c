/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_init_constants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:09:10 by overetou          #+#    #+#             */
/*   Updated: 2021/01/20 16:52:58 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		sha_init_hash(t_sha_data *data)
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

static void	assign_3_uint(unsigned int *tab, unsigned int u1,
unsigned int u2, unsigned int u3)
{
	tab[0] = u1;
	tab[1] = u2;
	tab[2] = u3;
}

static void	sha256_reamaining_constants(t_sha_data *data)
{
	assign_3_uint((data->constants) + 36, 0x650a7354, 0x766a0abb, 0x81c2c92e);
	data->constants[39] = 0x92722c85;
	assign_3_uint((data->constants) + 40, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70);
	data->constants[43] = 0xc76c51a3;
	assign_3_uint((data->constants) + 44, 0xd192e819, 0xd6990624, 0xf40e3585);
	data->constants[47] = 0x106aa070;
	assign_3_uint((data->constants) + 48, 0x19a4c116, 0x1e376c08, 0x2748774c);
	data->constants[51] = 0x34b0bcb5;
	assign_3_uint((data->constants) + 52, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f);
	data->constants[55] = 0x682e6ff3;
	assign_3_uint((data->constants) + 56, 0x748f82ee, 0x78a5636f, 0x84c87814);
	data->constants[59] = 0x8cc70208;
	assign_3_uint((data->constants) + 60, 0x90befffa, 0xa4506ceb, 0xbef9a3f7);
	data->constants[63] = 0xc67178f2;
}

void		sha256_init_constants(t_sha_data *data)
{
	assign_3_uint((data->constants), 0x428a2f98, 0x71374491, 0xb5c0fbcf);
	data->constants[3] = 0xe9b5dba5;
	assign_3_uint((data->constants) + 4, 0x3956c25b, 0x59f111f1, 0x923f82a4);
	data->constants[7] = 0xab1c5ed5;
	assign_3_uint((data->constants) + 8, 0xd807aa98, 0x12835b01, 0x243185be);
	data->constants[11] = 0x550c7dc3;
	assign_3_uint((data->constants) + 12, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7);
	data->constants[15] = 0xc19bf174;
	assign_3_uint((data->constants) + 16, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6);
	data->constants[19] = 0x240ca1cc;
	assign_3_uint((data->constants) + 20, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc);
	data->constants[23] = 0x76f988da;
	assign_3_uint((data->constants) + 24, 0x983e5152, 0xa831c66d, 0xb00327c8);
	data->constants[27] = 0xbf597fc7;
	assign_3_uint((data->constants) + 28, 0xc6e00bf3, 0xd5a79147, 0x06ca6351);
	data->constants[31] = 0x14292967;
	assign_3_uint((data->constants) + 32, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc);
	data->constants[35] = 0x53380d13;
	sha256_reamaining_constants(data);
}
