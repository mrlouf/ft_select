/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:48:52 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* This function works very similarly from ft_memset, except that it replaces
every character with NULL and returns nothing. */

void	ft_bzero(void *b, size_t len)
{
	char	*s;

	s = (char *)b;
	while (len-- > 0)
		*(s++) = '\0';
	return ;
}

/*
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("av = %d\n", av[1]);
		bzero(av[1], 3);
		printf("av = %d\n", av[1]);
	}
	return (0);
}*/
