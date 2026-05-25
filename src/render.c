/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 16:26:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	draw_arguments(struct s_select *s)
{
	int	i;

	i = 0;
	while (i < s->win_size.ws_row - 1 && i < s->ac)
	{
		append_buffer(s, s->av[i], ft_strlen(s->av[i]));
		append_buffer(s, "\r\n", 2);
		i++;
	}
}

/* static void	editor_draw_cursor(char **buf)
{
	buf[0][0] = '\x1b';
	buf[0][1] = '[';
	buf[0][2] = s->cursor.y + 1 + '0';
	buf[0][3] = ';';
	buf[0][4] = s->cursor.x + 1 + '0';
	buf[0][5] = 'H';
	buf[0][6] = '\0';
} */

void	refresh_screen(struct s_select *s)
{
	char	buf[7];

	tc_clear_screen();
	append_buffer(s, "\x1b[H", 3);
	draw_arguments(s);
	buf[0] = '\x1b';
	buf[1] = '[';
	buf[2] = s->cursor.y + 1 + '0';
	buf[3] = ';';
	buf[4] = s->cursor.x + 1 + '0';
	buf[5] = 'H';
	buf[6] = '\0';
	append_buffer(s, buf, 7);
	append_buffer(s, "\x1b[?25h", 6);
}

void	render_terminal(struct s_select *s)
{
	refresh_screen(s);
	write_buffer(s->fd_tty, s->buf);
	clear_buffer(s);
}
