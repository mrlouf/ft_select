/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:12:21 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	unsigned char	c;

	c = 0;
	while (c <= 127)
	{
		printf("%c = %d = %d\n", c, ft_isdigit(c), isdigit(c));
		c++;
	}
	return (0);
}*/
