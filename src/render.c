/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 14:31:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	editor_draw_arguments(struct s_select *s)
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

void	editor_refresh_screen(struct s_select *s)
{
	tc_clear_screen();
	append_buffer(s, "\x1b[H", 3);

	editor_draw_arguments(s);

	char	buf[32];
	snprintf(buf, 32, "\x1b[%d;%dH", s->cursor.y+1, s->cursor.x+1);
	append_buffer(s, buf, ft_strlen(buf));

	append_buffer(s, "\x1b[?25h", 6);
}

void	render_terminal(struct s_select *s)
{
	editor_refresh_screen(s);
	write_buffer(s->fd_tty, s->buf);
	clear_buffer(s);
}
