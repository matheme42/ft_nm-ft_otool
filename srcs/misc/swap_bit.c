/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:01:51 by gpouyat           #+#    #+#             */
/*   Updated: 2018/10/08 12:44:16 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

/*
** swap						0x de ad be ef
** ((x & 0xff000000) >> 24)	0x 00 00 00 de
** ((x & 0x00ff0000) >>  8)	0x 00 00 ad 00
** ((x & 0x0000ff00) <<  8)	0x 00 be 00 00
** ((x & 0x000000ff) << 24)	0x ef 00 00 00
** =>						0x ef be ad de
*/

uint16_t	ft_swap_int16(uint16_t x)
{
	return (((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
}

uint32_t	ft_swap_int32(uint32_t x)
{
	return (((x & 0xff000000) >> 24) | \
			((x & 0x00ff0000) >> 8) | \
			((x & 0x0000ff00) << 8) | \
			((x & 0x000000ff) << 24));
}

uint64_t	ft_swap_int64(uint64_t x)
{
	return (((x & 0xff00000000000000ULL) >> 56) | \
			((x & 0x00ff000000000000ULL) >> 40) | \
			((x & 0x0000ff0000000000ULL) >> 24) | \
			((x & 0x000000ff00000000ULL) >> 8) | \
			((x & 0x00000000ff000000ULL) << 8) | \
			((x & 0x0000000000ff0000ULL) << 24) | \
			((x & 0x000000000000ff00ULL) << 40) | \
			((x & 0x00000000000000ffULL) << 56));
}
