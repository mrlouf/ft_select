/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 15:44:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

/* 
	Read a key input from the user and return it.
	This function will block until a key is pressed.
*/
int	read_key(void)
{
	int		nread;
	char	seq[3];

	nread = read(STDIN_FILENO, seq, 3);
	if (nread == -1 && errno != EAGAIN && errno != EINTR)
		fatal_error("could not read key input");
	if (seq[0] == '\x1b')
	{
		if (seq[1] == '[')
		{
			if (seq[2] == '\0')
				return (KEY_ESCAPE);
			if (seq[2] == 'A')
				return (KEY_UP);
			if (seq[2] == 'B')
				return (KEY_DOWN);
			if (seq[2] == 'C')
				return (KEY_RIGHT);
			if (seq[2] == 'D')
				return (KEY_LEFT);
		}
		else
			return (KEY_ESCAPE);
	}
	return (KEY_UNKNOWN);
}

static int	is_moving_key(int key)
{
	return (key == KEY_UP
		|| key == KEY_DOWN
		|| key == KEY_LEFT
		|| key == KEY_RIGHT);
}

static int	is_ctrl_key(int key)
{
	return (key == KEY_SPACE || key == KEY_ENTER || key == KEY_ESCAPE
		|| key == KEY_BACKSPACE || key == KEY_DELETE);
}

void	process_keypress(struct s_select *s)
{
	int	key;

	key = read_key();
	if (is_ctrl_key(key))
	{
		control_key(s, key);
	}
	else if (is_moving_key(key))
	{
		move_cursor(s, key);
	}
}
