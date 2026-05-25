/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 20:20:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 13:16:00 by nicolas          ###   ########.fr       */
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
	}
	else
	{
		g_win_size.ws_col = ws.ws_col;
		g_win_size.ws_row = ws.ws_row;
		return (0);
	}
}

/* 
	Disable raw mode and restore the original terminal settings.
	This MUST be called before exiting the program
	to ensure the terminal is left in a usable state,
	regardless of how the program exits (normal exit, error, signal, etc).
*/
void	disable_raw_mode(void)
{
	ft_putstr_fd("\x1b[?25h", STDOUT_FILENO);
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	tputs(tgetstr("te", NULL), 1, ft_putchar);
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
}

/* 
	Enable raw mode for the terminal.
	This will disable canonical mode, echoing, and other features
	that would interfere with our ability to read keypresses directly.
*/
void	enable_raw_mode(struct s_select *s)
{
	struct termios	raw;
	char			*term;

	raw = g_orig_termios;
	tputs(tgetstr("ti", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		fatal_error("tcgetattr failed", s);
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
