/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 19:34:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

static void	fatal_error(const char *s)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	disable_raw_mode(struct termios *orig_termios)
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

int	ft_select(char **options, int count)
{
	char	c;

	while (1)
	{
		c = '\0';

		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			fatal_error("read");
		if (ft_iscntrl(c))
			printf("%d\r\n", c);
		else
			printf("%d ('%c')\r\n", c, c);
		if (c == 'q')
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct termios	orig_termios;

	tcgetattr(STDIN_FILENO, &orig_termios);
	enable_raw_mode();
	ft_select(av + 1, ac - 1);
	disable_raw_mode(&orig_termios);
	return (0);
}
