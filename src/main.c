/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/15 10:35:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	fatal_error(const char *str, struct s_select *s)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	disable_raw_mode(s);
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
	return (0);
}

int	main(int ac, char **av)
{
	struct s_select	s;

	s.orig_termios = (struct termios){0};
	s.win_size = (struct winsize){0};
	s.buf = (struct s_string){NULL, 0};
	s.cursor = (struct s_cursor){0, 0};
	s.av = av + 1;
	s.ac = ac - 1;

	// * DEBUG: Open a log file to write debug information to
	s.fd_logfile = -1;
	if ((s.fd_logfile = open("ft_select.log", O_WRONLY | O_CREAT, 0644)) == -1)
		fatal_error("Unable to open log file", &s);

	tcgetattr(STDIN_FILENO, &s.orig_termios);
	enable_raw_mode(&s);
	ft_select(&s);
	disable_raw_mode(&s);

	// * DEBUG: Close the log file if opened
	if (s.fd_logfile != -1)
		close(s.fd_logfile);
	return (0);
}
