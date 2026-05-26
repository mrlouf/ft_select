/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:15:26 by nponchon          #+#    #+#             */
/*   Updated: 2026/05/26 10:45:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	**failure(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**get_strs(char **strs, const char *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
			len++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			strs[j] = ft_substr(s, (i - len + 1), len);
			if (!strs[j++])
				return (failure(strs));
			len = 0;
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	cw;

	cw = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (cw + 1));
	if (!strs)
		return (NULL);
	strs = get_strs(strs, s, c);
	return (strs);
}
/*
int	main(int ac, char **av)
{
	char	**res;
	int		i;

	i = 0;
	if (ac == 3)
	{
		res = ft_split(av[1], av[2][0]);
		while (res[i])
		{
			printf("%s\n", res[i]);
			free(res[i]);
			i++;
		}
		free(res);
	}
	return (0);
}*/
