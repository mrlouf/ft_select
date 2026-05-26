/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 18:41:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	draw_arguments(struct s_select *s)
{
	int	i;
	int j;

	i = 0;
	while (i < s->win_size.ws_row - 1 && i < s->ac)
	{
		if (s->av[i] == NULL)
		{
			i++;
			continue ;
		}
		tc_putstr(s, TILDE);
		j = 0;
		while (j < (int)ft_strlen(s->av[i]) && j < s->win_size.ws_col - 1)
		{
			if (s->selected & (1 << i))
				tc_invert_colours(s);
			if (i+1 == s->cursor.y && j+TILDE_OFFSET == s->cursor.x)
			{
				tc_start_underline(s);
				tc_invert_colours(s);
			}
			tc_putchar(s, s->av[i][j]);
			tc_stop_underline(s);
			tc_reset_colours(s);
			j++;
		}
		tc_putendl(s);
		i++;
	}
}

static void	draw_header(struct s_select *s)
{
	tc_putstr(s, HEADER_INFO);
	tc_putendl(s);
}

static void	refresh_screen(struct s_select *s)
{
	tc_clear_screen(s);
	// append_buffer(s, tgoto(s->termcaps.cm, 0, 0), ft_strlen(tgoto(s->termcaps.cm, 0, 0)));
	draw_header(s);
	draw_arguments(s);
	tc_move_cursor(s);
	tc_set_cursor_visibility(s, 1);
}

void	render_terminal(struct s_select *s)
{
	refresh_screen(s);
	write_buffer(g_fd_tty, s->buf);
	clear_buffer(s);
}
