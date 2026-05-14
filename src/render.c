/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 21:58:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	editor_draw_arguments(struct s_select *s)
{
/* 	int	i;

	i = 0;
	while (i < s->win_size.ws_row - 1 && i < s->ac)
	{
		append_buffer(s, s->av[i], ft_strlen(s->av[i]));
		append_buffer(s, "\r\n", 2);
		i++;
	} */

	for (int i = 0; i < s->win_size.ws_row - 1; i++)
	{
		for (int j = 0; j < s->win_size.ws_col - 1; j++)
		{
			append_buffer(s, "*", 1);
		}
		append_buffer(s, "\r\n", 2);
	}
}

void	editor_refresh_screen(struct s_select *s)
{
	append_buffer(s, "\x1b[?25l", 6);
	append_buffer(s, "\x1b[2J", 4);
	append_buffer(s, "\x1b[H", 3);

	editor_draw_arguments(s);

	append_buffer(s, "\x1b[H", 3);
	append_buffer(s, "\x1b[?25h", 6);
}

void	render_terminal(struct s_select *s)
{
	editor_refresh_screen(s);
	append_buffer(s, "\x1b[H", 3);
	write_buffer(s->buf);
	clear_buffer(s);
}
