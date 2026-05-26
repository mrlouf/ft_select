/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 10:52:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	tc_invert_colours(struct s_select *s)
{
	append_buffer(s, s->termcaps.mr, ft_strlen(s->termcaps.mr));
}

void	tc_reset_colours(struct s_select *s)
{
	append_buffer(s, s->termcaps.me, ft_strlen(s->termcaps.me));
}

void	tc_set_cursor_visibility(struct s_select *s, int invisible)
{
	if (invisible)
		append_buffer(s, s->termcaps.ve, ft_strlen(s->termcaps.ve));
	else
		append_buffer(s, s->termcaps.vi, ft_strlen(s->termcaps.vi));
}

void	tc_putstr(struct s_select *s, const char *str)
{
	append_buffer(s, str, ft_strlen(str));
}

void	tc_putendl(struct s_select *s)
{
	append_buffer(s, "\r\n", 2);
}

void	tc_move_cursor(struct s_select *s)
{
	char	*pos;

	pos = tgoto(s->termcaps.cm, s->cursor.x, s->cursor.y);
	append_buffer(s, pos, ft_strlen(pos));
}

void	tc_clear_screen(struct s_select *s)
{
	char	*cl;

	cl = s->termcaps.cl;
	append_buffer(s, cl, ft_strlen(cl));
}

void	tc_start_underline(struct s_select *s)
{
	append_buffer(s, "\E[4m", 4);
}

void	tc_stop_underline(struct s_select *s)
{
	append_buffer(s, "\E[24m", 5);
}
