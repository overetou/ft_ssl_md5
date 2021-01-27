/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:30:24 by overetou          #+#    #+#             */
/*   Updated: 2021/01/25 16:35:37 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	memcopy(char *dest, const char *src, int size)
{
	int	i;

	i = 0;
	while (i != size)
	{
		dest[i] = src[i];
		i++;
	}
}

void	error_if_null(void *p, const char *err_msg)
{
	if (p)
		return ;
	error_msg(err_msg);
}

void	*secure_malloc(int size)
{
	void	*new;

	new = malloc(size);
	error_if_null(new, "Allocation Failure\n");
	return (new);
}

void	*secure_realloc(void *ptr, int ptr_size, int size)
{
	void	*new;

	new = secure_malloc(size);
	memcopy(new, ptr, ptr_size);
	free(ptr);
	return (new);
}

void	error_msg(const char *msg)
{
	putstr(msg);
	exit(0);
}
