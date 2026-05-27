/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/27 17:30:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	write_single_argument(struct s_select *s, int i)
{
	int	j;

	tc_putstr(s, TILDE);
	j = 0;
	while (j < (int)ft_strlen(s->av[i]) && j < s->win_size.ws_col - 1)
	{
		if (s->selected & (1 << i))
			tc_invert_colours(s);
		if (i + 1 == s->cursor.y)
			tc_start_underline(s);
		tc_putchar(s, s->av[i][j]);
		if (i + 1 == s->cursor.y)
			tc_stop_underline(s);
		tc_reset_colours(s);
		j++;
	}
	tc_putendl(s);
}

static void	iterate_over_arguments(struct s_select *s)
{
	int	i;

	i = 0;
	while (i < s->win_size.ws_row - 1 && i < s->ac)
	{
		if (s->av[i] == NULL)
		{
			i++;
			continue ;
		}
		write_single_argument(s, i);
		i++;
	}
}

static void	fill_buffer(struct s_select *s)
{
	tc_clear_screen(s);
	tc_hide_cursor(s);
	tc_putstr(s, HEADER_INFO);
	tc_putendl(s);
	iterate_over_arguments(s);
	tc_move_cursor(s);
}

void	render_terminal(struct s_select *s)
{
	fill_buffer(s);
	write_buffer(g_fd_tty, s->buf);
	clear_buffer(s);
}
