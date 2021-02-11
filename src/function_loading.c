/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_loading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:09:26 by overetou          #+#    #+#             */
/*   Updated: 2021/01/22 16:24:50 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void				add_final_exec_func(t_master *m, void (*f)(t_master*))
{
	m->final_exec_funcs = secure_realloc(m->final_exec_funcs,
	m->final_funcs_number * sizeof(void*), (m->final_funcs_number + 1)
	* sizeof(void*));
	(m->final_exec_funcs)[m->final_funcs_number] = f;
	(m->final_funcs_number)++;
}

unsigned long long	remainer_to_64_bytes(unsigned long long l)
{
	unsigned long long	mod;

	mod = l % 64;
	if (mod)
		return (64 - mod);
	return (0);
}

void				invert_endian(unsigned char *u, int l)
{
	unsigned char t;

	while (l > 1)
	{
		l--;
		t = *u;
		*u = u[l];
		u[l] = t;
		u++;
		l--;
	}
}

void				long_memcopy(unsigned char *dest,
		const unsigned char *src, unsigned long long len)
{
	unsigned long long	i;

	i = 0;
	while (i != len)
	{
		dest[i] = src[i];
		i++;
	}
}

void				load_hashable_blocks(const unsigned char *msg,
t_sha_data *d)
{
	unsigned long long	padding;

	d->full_len = d->msg_len;
	d->full_len += 1;
	d->full_len += 8;
	padding = remainer_to_64_bytes(d->full_len);
	d->full_len += padding;
	d->blocks = malloc(d->full_len);
	long_memcopy(d->blocks, msg, d->msg_len);
	d->blocks[d->msg_len] = 0b10000000;
	b_zero(d->blocks + d->msg_len + 1, padding);
	*((unsigned long long*)(d->blocks + d->full_len - 8)) = d->msg_len * 8;
	invert_endian(d->blocks + d->full_len - 8, 8);
}
