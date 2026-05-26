/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:14:33 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* This function takes a pointer to void (i.e. to any type of bytes), makes a
temporary copy of it and iterates the copy to replace the current byte by c
before returning the original pointer */

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*cpy;

	cpy = (unsigned char *)dest;
	while (len-- > 0)
		*(cpy++) = (unsigned char)c;
	return (dest);
}

/*
int	main(int ac, char **av)
{
	int	c = '*';
	char	*str;
	if (ac == 2)
	{
		str = av[1];
		printf("dest = %s\n", (char *)ft_memset(av[1], c, 3));
		printf("dest = %s\n", (char *)memset(av[1], c, 3));
		
	}
	return (0);
}*/
