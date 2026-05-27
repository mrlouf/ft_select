/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/27 20:08:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	set_text_attributes(struct s_select *s, int i)
{
	struct stat	info;

	if (!(stat(s->av[i], &info)))
	{
		if (S_ISDIR(info.st_mode))
			tc_putstr(s, "\033[34m");
		else if (info.st_mode & S_IXUSR)
			tc_putstr(s, "\033[32m");
		if (S_ISLNK(info.st_mode))
			tc_putstr(s, "\033[36m");
		else if (S_ISSOCK(info.st_mode))
			tc_putstr(s, "\033[35m");
		else if (S_ISFIFO(info.st_mode))
			tc_putstr(s, "\033[1;33m");
		else if (S_ISCHR(info.st_mode))
			tc_putstr(s, "\033[1;33m");
		else if (S_ISBLK(info.st_mode))
			tc_putstr(s, "\033[1;33m");
	}
}

static void	write_single_argument(struct s_select *s, int i)
{
	int	j;

	tc_putstr(s, TILDE);
	set_text_attributes(s, i);
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
		j++;
	}
	tc_reset_colours(s);
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
		tc_reset_colours(s);
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
