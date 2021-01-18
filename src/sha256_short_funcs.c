/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_short_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:00:18 by overetou          #+#    #+#             */
/*   Updated: 2021/01/18 16:00:19 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
