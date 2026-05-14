/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 20:10:33 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	fatal_error(const char *s)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	disable_raw_mode(struct termios *orig_termios)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios) == -1)
		fatal_error("tcsetattr");
}

static void	enable_raw_mode(void)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &raw) == -1)
		fatal_error("tcgetattr");
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static int	ft_select(char **options, int count, struct s_select *s)
{
	while (1)
	{
		editor_refresh_screen();
		editor_process_keypress(s);
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct s_select	s;

	s.orig_termios = (struct termios){0};

	tcgetattr(STDIN_FILENO, &s.orig_termios);
	enable_raw_mode();
	ft_select(av + 1, ac - 1, &s);
	disable_raw_mode(&s.orig_termios);
	return (0);
}
