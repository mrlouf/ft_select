/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 20:09:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

char	editor_read_key(void)
{
	int		nread;
	char	c;

	nread = read(STDIN_FILENO, &c, 1);

	while (nread != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			fatal_error("read");
		nread = read(STDIN_FILENO, &c, 1);
	}
	return (c);
}

void	editor_process_keypress(struct s_select *s)
{
	char	c;

	c = editor_read_key();
	if (c == 27)
	{
		disable_raw_mode(&s->orig_termios);
		exit(EXIT_SUCCESS);
	}
}

int	ctrl_key(const int k)
{
	return (k & 0x1f);
}
