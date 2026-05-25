/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 20:20:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 15:24:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

int	get_window_size(void)
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
	return (-1);
}

void	log_info(struct s_select *s, const char *str)
{
	if (s->fd_logfile != -1)
	{
		ft_putstr_fd("LOG: ", s->fd_logfile);
		ft_putendl_fd((char *)str, s->fd_logfile);
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
	char	*buf[2048];
	char	*cap;

	ft_bzero(buf, sizeof(buf));
	cap = tgetstr("ve", buf);
	if (cap)
		tputs(cap, 1, ft_putchar);
	cap = tgetstr("me", buf);
	if (cap)
		tputs(cap, 1, ft_putchar);
	cap = tgetstr("te", buf);
	if (cap)
		tputs(cap, 1, ft_putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
}

/* 
	Enable raw mode for the terminal.
	This will disable canonical mode, echoing, and other features
	that would interfere with our ability to read keypresses directly.
*/
void	enable_raw_mode(void)
{
	struct termios	raw;
	char			*buf[2048];
	char			*cap;

	raw = g_orig_termios;
	cap = tgetstr("ti", buf);
	if (cap)
		tputs(cap, 1, ft_putchar);
	cap = tgetstr("vi", buf);
	if (cap)
		tputs(cap, 1, ft_putchar);
	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		fatal_error("tcgetattr failed to enable raw mode");
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
