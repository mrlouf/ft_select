/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/15 10:55:25 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

/* 
	Read a key input from the user and return it.
	This function will block until a key is pressed.
*/
char	editor_read_key(struct s_select *s)
{
	int		nread;
	char	c;
	char	seq[3];

	nread = 0;
	while (nread != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			fatal_error("read failed", s);
		nread = read(STDIN_FILENO, &c, 1);
	}
	if (c == '\x1b')
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return ('\x1b');
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return ('\x1b');
		if (seq[0] == '[')
		{
			if (seq[1] == 'A')
				return ('w');
			if (seq[1] == 'B')
				return ('s');
			if (seq[1] == 'C')
				return ('d');
			if (seq[1] == 'D')
				return ('a');
		}
		return ('\x1b');
	}
	else
		return (c);
}

void	editor_process_keypress(struct s_select *s)
{
	char	c;

	c = editor_read_key(s);

	char	buf[32];

	#include <stdio.h>
	snprintf(buf, 32, "Key pressed: %d", c);
	log_info(s, buf);

	if (c == 27)
	{
		disable_raw_mode(s);
		exit(EXIT_SUCCESS);
	}
	else if (c == 's')
		s->cursor.y++;
	else if (c == 'w')
		s->cursor.y--;
	else if (c == 'd')
		s->cursor.x++;
	else if (c == 'a')
		s->cursor.x--;
}

int	ctrl_key(const int k)
{
	return (k & 0x1f);
}
