/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:25:06 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 16:25:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_select.h"

void	tc_putstr(struct s_select *s, const char *str)
{
	append_buffer(s, str, ft_strlen(str));
}

void	tc_putchar(struct s_select *s, char c)
{
	append_buffer(s, (char []){c, '\0'}, 1);
}

void	tc_putendl(struct s_select *s)
{
	append_buffer(s, "\r\n", 2);
}

void	tc_clear_screen(struct s_select *s)
{
	char	*cl;

	cl = s->termcaps.cl;
	append_buffer(s, cl, ft_strlen(cl));
}
