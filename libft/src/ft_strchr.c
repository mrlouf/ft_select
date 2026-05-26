/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:19:12 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*	This function looks for the first occurence of c in the string s.
 *	It returns the address of the occurence if found, or NULL if no
 *	occurence is found.
 *	If the character to find is '\0', the function basically returns 
 *	the end of the string.
 *	Important: the int c has to be converted into a char for the search. */

char	*ft_strchr(const char *s, int c)
{
	char		cc;

	cc = (char) c;
	while (*s)
	{
		if (*s == cc)
			return ((char *) s);
		s++;
	}
	if (*s == cc)
		return ((char *) s);
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	char c = ' ';
	if (ac == 2)
		ft_strchr(av[1], c);
	return (0);
}*/
