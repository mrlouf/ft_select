/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 16:10:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static int	get_arrow_key(int key)
{
	if (key == 'A')
		return (KEY_UP);
	if (key == 'B')
		return (KEY_DOWN);
	if (key == 'C')
		return (KEY_RIGHT);
	if (key == 'D')
		return (KEY_LEFT);
	return (KEY_UNKNOWN);
}

/* 
	Read a key input from the user and return it.
	This function will block until a key is pressed.
*/
int	read_key(void)
{
	int		nread;
	char	seq[4];

	nread = read(STDIN_FILENO, seq, 4);
	if (nread == -1 && errno != EAGAIN && errno != EINTR)
		fatal_error("could not read key input");
	if (nread == 1)
	{
		if (seq[0] == 127)
			return (KEY_BACKSPACE);
		else if (seq[0] == ' ')
			return (KEY_SPACE);
		else if (seq[0] == '\r' || seq[0] == '\n')
			return (KEY_ENTER);
		else if (seq[0] == '\x1b')
			return (KEY_ESCAPE);
	}
	if (nread == 3 && seq[1] == '[')
		return (get_arrow_key(seq[2]));
	if (nread == 4 && seq[2] == '3' && seq[3] == '~')
		return (KEY_DELETE);
	return (KEY_UNKNOWN);
}

static int	is_control_key(int key)
{
	return (key == KEY_SPACE || key == KEY_ENTER || key == KEY_BACKSPACE
		|| key == KEY_DELETE || key == KEY_ESCAPE);
}

static int	is_arrow_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN
		|| key == KEY_LEFT || key == KEY_RIGHT);
}

void	process_keypress(struct s_select *s)
{
	int	key;

	key = read_key();
	if (is_control_key(key))
	{
		control_key(s, key);
	}
	else if (is_arrow_key(key))
	{
		move_cursor(s, key);
	}
}
