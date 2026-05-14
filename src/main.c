/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 22:03:48 by nicolas          ###   ########.fr       */
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

	tcgetattr(STDIN_FILENO, &s.orig_termios);
	enable_raw_mode(&s);
	ft_select(&s);
	disable_raw_mode(&s);
	return (0);
}
