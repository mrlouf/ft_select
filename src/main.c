/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:14:57 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 19:03:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

static void	disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

static void	enable_raw_mode(void)
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	ft_select(char **options, int count)
{
	char c;
  
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 27) {
    if (ft_iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }
  }

	return (0);
}

int	main(int ac, char **av)
{
	struct termios orig_termios;

	tcgetattr(STDIN_FILENO, &orig_termios);
	enable_raw_mode();
  
	ft_select(av + 1, ac - 1);

	disable_raw_mode(&orig_termios);
	return (0);
}
