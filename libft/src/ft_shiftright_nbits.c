/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shiftright_nbits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:37:56 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/28 12:41:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
	This function set the n-th bit of the selected variable to 0,
	effectively deselecting the argument at index n.
	The right part (lower) keeps all bits below n, and the left part (upper)
	shifts all bits above n down by one to fill the gap.
*/
u_int64_t	shift_selected_bits(u_int64_t bits, int n)
{
	u_int64_t	lower;
	u_int64_t	upper;

	lower = bits & ((1ULL << n) - 1);
	upper = bits >> (n + 1);
	return (lower | (upper << n));
}
