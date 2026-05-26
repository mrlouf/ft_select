/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:09 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	const unsigned char	*cpy;
	unsigned char		cc;

	cpy = (const unsigned char *)s;
	cc = (unsigned char)c;
	while (len > 0)
	{
		if (*cpy == cc)
			return ((void *)cpy);
		cpy++;
		len--;
	}
	return (NULL);
}
