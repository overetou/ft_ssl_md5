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
