/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 10:52:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	draw_arguments(struct s_select *s)
{
	int	i;

	i = 0;
	while (i < s->win_size.ws_row - 1 && i < s->ac)
	{
		tc_putstr(s, "> ");
		if (i == s->cursor.y)
			tc_invert_colours(s);
		tc_putstr(s, s->av[i]);
		tc_reset_colours(s);
		tc_putendl(s);
		i++;
	}
}

static void	refresh_screen(struct s_select *s)
{
	tc_clear_screen(s);
	draw_arguments(s);
	tc_move_cursor(s);
	tc_start_underline(s);
	tc_putstr(s, " ");
	tc_stop_underline(s);
	tc_set_cursor_visibility(s, 1);
}

void	render_terminal(struct s_select *s)
{
	refresh_screen(s);
	write_buffer(s->fd_tty, s->buf);
	clear_buffer(s);
}
