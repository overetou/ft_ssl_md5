/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_execute_loaded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:43:21 by overetou          #+#    #+#             */
/*   Updated: 2021/01/18 15:43:57 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_set_end_bits_len(UCHAR *adr, unsigned long val)
{
	int				i;
	int				j;
	UCHAR	*vals;

	i = 7;
	j = 0;
	vals = (UCHAR*)(&val);
	while (i >= 0)
	{
		adr[i] = vals[j];
		i--;
		j++;
	}
}

void	exec_final_funcs(t_master *m)
{
	int i;

	i = 0;
	while (i != m->final_funcs_number)
	{
		m->final_exec_funcs[i](m);
		i++;
	}
	free(m->final_exec_funcs);
}

void	exec_files_hash_and_funcs(t_master *m)
{
	int	i;

	i = 0;
	while (i != m->files_to_hash_nb)
	{
		exec_file_hash(m, m->files_to_hash[i]);
		i++;
	}
	free(m->files_to_hash);
	if (m->final_funcs_number)
		exec_final_funcs(m);
}

void	md5_execute_loaded(t_master *m)
{
	UCHAR	*md5sum;

	if (m->files_to_hash_nb)
		exec_files_hash_and_funcs(m);
	else
	{
		if (m->final_funcs_number)
			exec_final_funcs(m);
		else
		{
			load_stdin(m);
			md5sum = md5_digest(m->stdin_string);
			disp_sum(md5sum, 16);
			free(md5sum);
			free(m->stdin_string);
			putstr("\n");
		}
	}
}
