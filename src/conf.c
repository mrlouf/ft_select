/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 20:20:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/28 12:43:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	fatal_error(const char *str)
{
	disable_raw_mode();
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	get_window_size(struct s_select *s)
{
	struct winsize	ws;

	if (ioctl(g_fd_tty, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		if (write(g_fd_tty, "\x1b[999C\x1b[999B", 12) != 12)
			return (-1);
	}
	else
	{
		s->win_size.ws_col = ws.ws_col;
		s->win_size.ws_row = ws.ws_row;
		return (0);
	}
	return (-1);
}

/* 
	Disable raw mode and restore the original terminal settings.
	This MUST be called before exiting the program
	to ensure the terminal is left in a usable state,
	regardless of how the program exits (normal exit, error, signal, etc).
*/
void	disable_raw_mode(void)
{
	char	buf[2048];
	char	*cap;

	ft_bzero(buf, sizeof(buf));
	cap = buf;
	cap = tgetstr("ve", &cap);
	if (cap)
		tputs(cap, 1, tc_callback);
	cap = tgetstr("me", &cap);
	if (cap)
		tputs(cap, 1, tc_callback);
	cap = tgetstr("te", &cap);
	if (cap)
		tputs(cap, 1, tc_callback);
	tcsetattr(g_fd_tty, TCSANOW, &g_orig_termios);
}

/* 
	Enable raw mode for the terminal.
	This will disable canonical mode, echoing, and other features
	that would interfere with our ability to read keypresses directly.
*/
void	enable_raw_mode(void)
{
	struct termios	raw;
	char			buf[2048];
	char			*cap;

	raw = g_orig_termios;
	ft_bzero(buf, sizeof(buf));
	cap = buf;
	cap = tgetstr("ti", &cap);
	if (cap)
		tputs(cap, 1, tc_callback);
	cap = tgetstr("vi", &cap);
	if (cap)
		tputs(cap, 1, tc_callback);
	if (tcgetattr(g_fd_tty, &raw) == -1)
		fatal_error("tcgetattr failed to enable raw mode");
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(g_fd_tty, TCSANOW, &raw);
}
