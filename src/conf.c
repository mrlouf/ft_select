/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 20:20:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 13:28:41 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

int	get_window_size(struct s_select *s)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
			return (-1);
		editor_read_key(s);
		return (-1);
	}
	else
	{
		s->win_size.ws_col = ws.ws_col;
		s->win_size.ws_row = ws.ws_row;
		return (0);
	}
}

void	disable_raw_mode(struct s_select *s)
{
	tputs(tgetstr("ve", NULL), 1, putchar);
	tputs(tgetstr("me", NULL), 1, putchar);
	tputs(tgetstr("te", NULL), 1, putchar);
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->orig_termios) == -1)
		fatal_error("tcsetattr failed", s);
	log_info(s, "Raw mode disabled, terminal should be cleaned up");
}

void	enable_raw_mode(struct s_select *s)
{
	struct termios	raw;

	raw = s->orig_termios;
	tgetent(NULL, getenv("TERM"));
	tputs(tgetstr("ti", NULL), 1, putchar);
	tputs(tgetstr("vi", NULL), 1, putchar);
	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		fatal_error("tcgetattr failed", s);
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
