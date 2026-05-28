/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/28 11:30:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

// Keep the original terminal settings so we can restore them on exit
// This is global so it can be accessed from signal handlers
struct termios	g_orig_termios;
int				g_fd_tty = -1;

/* 
	The main loop of the ft_select program.
	It will continuously get the window size, render the terminal,
	and process keypresses until the user exits.
*/
static int	ft_select(struct s_select *s)
{
	enable_raw_mode();
	tc_clear_screen(s);
	while (1)
	{
		if (get_window_size(s) == -1)
			fatal_error("Unable to get window size");
		render_terminal(s);
		process_keypress(s);
	}
	disable_raw_mode();
	return (0);
}

static int	check_environment(void)
{
	char	*term;

	if (!isatty(g_fd_tty))
	{
		ft_putstr_fd("Error: /dev/tty is not a tty\n", STDERR_FILENO);
		return (-1);
	}
	term = getenv("TERM");
	if (!term)
	{
		ft_putstr_fd("Error: TERM env variable not set\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, term) <= 0)
	{
		ft_putstr_fd("Error: termcap database inaccessible\n", STDERR_FILENO);
		return (-1);
	}
	if (tcgetattr(g_fd_tty, &g_orig_termios) == -1)
	{
		ft_putstr_fd("Error: tcgetattr failed\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static void	initialise_select(struct s_select *s, int ac, char **av)
{
	g_fd_tty = open("/dev/tty", O_RDWR);
	if (g_fd_tty == -1)
		exit(EXIT_FAILURE);
	if (check_environment() == -1)
		exit(EXIT_FAILURE);
	s->buf = (struct s_string){NULL, 0};
	s->termcaps = (struct s_termcaps){0};
	s->cursor = (struct s_cursor){2, 1};
	s->av = av + 1;
	s->selected = 0 ^ 0;
	s->ac = ac - 1;
}

/* 
	Initialise the terminal capabilities:
	- cm: cursor movement
	- cl: clear screen
	- mr: enter reverse mode
	- me: exit reverse mode
	- vi: hide cursor
	- ve: show cursor
	- us: underline start
	- ue: underline end
*/
static void	initialise_termcaps(struct s_select *s)
{
	char	*buf[64];

	ft_bzero(buf, sizeof(buf));
	s->termcaps.cm = tgetstr("cm", buf);
	s->termcaps.cl = tgetstr("cl", buf);
	s->termcaps.mr = tgetstr("mr", buf);
	s->termcaps.me = tgetstr("me", buf);
	s->termcaps.vi = tgetstr("vi", buf);
	s->termcaps.ve = tgetstr("ve", buf);
	s->termcaps.smul = tgetstr("smul", buf);
	s->termcaps.rmul = tgetstr("rmul", buf);
}

int	main(int ac, char **av)
{
	struct s_select	s;

	if (ac < 1 || ac > 64)
	{
		ft_putstr_fd("Usage: ./ft_select args<1-64>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	initialise_select(&s, ac, av);
	initialise_termcaps(&s);
	setup_signal_handlers();
	ft_select(&s);
	if (s.buf.str)
		free(s.buf.str);
	return (0);
}
