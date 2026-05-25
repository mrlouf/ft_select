/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 13:26:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

struct termios	g_orig_termios;
struct winsize	g_win_size;
struct s_cursor	g_cursor;

void	fatal_error(const char *str, struct s_select *s)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	disable_raw_mode();
	exit(EXIT_FAILURE);
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
	The main loop of the ft_select program.
	It will continuously get the window size, render the terminal,
	and process keypresses until the user exits.
*/
static int	ft_select(struct s_select *s)
{
	while (1)
	{
		if (get_window_size(s) == -1)
			fatal_error("Unable to get window size", s);
		render_terminal(s);
		editor_process_keypress(s);
	}

	disable_raw_mode();
	tc_clear_screen();

	return (0);
}

static int check_environment(struct s_select *s)
{
	char *term;

	if (!isatty(STDIN_FILENO)) {
		ft_putstr_fd("Error: stdin is not a tty\n", STDERR_FILENO);
		return (-1);
	}
	term = getenv("TERM");
	if (!term) {
		ft_putstr_fd("Error: TERM environment variable not set\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, term) <= 0) {
		ft_putstr_fd("Error: Could not access the termcap database\n", STDERR_FILENO);
		return (-1);
	}
	if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1) {
		ft_putstr_fd("Error: tcgetattr failed\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static void	initialize_select(struct s_select *s)
{
	if (check_environment(s) == -1)
		exit(EXIT_FAILURE);

	s->buf = (struct s_string){NULL, 0};
	s->termcaps = (struct s_termcaps){0};
	s->av = NULL;
	s->ac = 0;
	s->fd_tty = -1;
	if ((s->fd_tty = open("/dev/tty", O_RDWR)) == -1)
		exit(EXIT_FAILURE);

	// * DEBUG: Open a log file to write debug information to
	s->fd_logfile = -1;
	if ((s->fd_logfile = open("ft_select.log", O_WRONLY | O_CREAT, 0644)) == -1)
		fatal_error("Unable to open log file", s);
}

int	main(int ac, char **av)
{
	struct s_select	s;

	initialize_select(&s);
	s.av = av + 1;
	s.ac = ac - 1;
	setup_signal_handlers(&s);

	enable_raw_mode(&s);
	ft_select(&s);
	disable_raw_mode();
	tc_clear_screen();

	// * DEBUG: Close the log file if opened
	if (s.fd_logfile != -1)
		close(s.fd_logfile);
	return (0);
}
