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

void	add_final_exec_func(t_master *m, void (*f)(t_master*))
{
	m->final_exec_funcs = secure_realloc(m->final_exec_funcs,
	m->final_funcs_number * sizeof(void*), (m->final_funcs_number + 1)
	* sizeof(void*));
	(m->final_exec_funcs)[m->final_funcs_number] = f;
	(m->final_funcs_number)++;
}

void	loop_start(t_sha_data *data)
{
	unsigned int	t;

	t = 0;
	while (t != 16)
	{
		data->w[t] = ((unsigned int*)(data->full_msg))[t];
		invert_endian((char*)(data->w + t), 4);
		t++;
	}
	while (t != 64)
	{
		data->w[t] = sig1((data->w)[t - 2]) + (data->w)[t - 7]
		+ sig0((data->w)[t - 15]) + (data->w)[t - 16];
		t++;
	}
	memcopy((char*)(data->a), (char*)(data->h), 8 * sizeof(int));
}

void	second_loop(t_sha_data *data)
{
	unsigned int	t;
	unsigned int	t1;
	unsigned int	t2;

	t = 0;
	while (t != 64)
	{
		t1 = data->a[7] + eps1(data->a[4]) + ch(data->a[4], data->a[5],
		data->a[6]) + data->constants[t] + ((unsigned int*)(data->w))[t];
		t2 = eps0(data->a[0]) + maj(data->a[0], data->a[1], data->a[2]);
		data->a[7] = data->a[6];
		data->a[6] = data->a[5];
		data->a[5] = data->a[4];
		data->a[4] = data->a[3] + t1;
		data->a[3] = data->a[2];
		data->a[2] = data->a[1];
		data->a[1] = data->a[0];
		data->a[0] = t1 + t2;
		t++;
	}
}

void	change_h(t_sha_data *data)
{
	data->bloc_pos += 64;
	data->h[0] += data->a[0];
	data->h[1] += data->a[1];
	data->h[2] += data->a[2];
	data->h[3] += data->a[3];
	data->h[4] += data->a[4];
	data->h[5] += data->a[5];
	data->h[6] += data->a[6];
	data->h[7] += data->a[7];
}
