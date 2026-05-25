/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 13:55:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

/* int	get_escape_key(char seq[3])
{
	if (seq[0] == '[') {
		if (seq[1] >= '0' && seq[1] <= '9') {
			if (read(STDIN_FILENO, &seq[2], 1) != 1)
				return '\x1b';
			if (seq[2] == '~') {
				switch (seq[1]) {
					case '1': return KEY_HOME;
					case '4': return KEY_END;
					case '5': return KEY_PAGE_UP;
					case '6': return KEY_PAGE_DOWN;
					case '7': return KEY_HOME;
					case '8': return KEY_END;
				}
			}
		} else {
			switch (seq[1]) {
			case 'A': return KEY_UP;
			case 'B': return KEY_DOWN;
			case 'C': return KEY_RIGHT;
			case 'D': return KEY_LEFT;
			case 'H': return KEY_HOME;
			case 'F': return KEY_END;
			}
		}
	} else if (seq[0] == 'O') {
		switch (seq[1]) {
			case 'H': return KEY_HOME;
			case 'F': return KEY_END;
		}
	}
	return '\x1b';
} */

/* 
	Read a key input from the user and return it.
	This function will block until a key is pressed.
*/
int editor_read_key(struct s_select *s)
{
	int nread;
	char c;
	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN && errno != EINTR)
			fatal_error("read", s);
	}
	if (c == '\x1b')
	{
		char seq[3];
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return (KEY_ESCAPE);
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return '\x1b';
		if (seq[0] == '[')
		{
			if (seq[1] >= '0' && seq[1] <= '9')
			{
				if (read(STDIN_FILENO, &seq[2], 1) != 1)
					return '\x1b';
			}
			else
			{
				switch (seq[1])
				{
				case 'A':
					return KEY_UP;
				case 'B':
					return KEY_DOWN;
				case 'C':
					return KEY_RIGHT;
				case 'D':
					return KEY_LEFT;
				}
			}
		}
		return '\x1b';
	}
	else
	{
		return c;
	}
}


static int	is_moving_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT);
}

static int	is_ctrl_key(int key)
{
	return (key == KEY_SPACE || key == KEY_ENTER || key == KEY_ESCAPE
		|| key == KEY_BACKSPACE || key == KEY_DELETE);
}

void	editor_process_keypress(struct s_select *s)
{
	int	c;

	c = editor_read_key(s);

	char	buf[32];
	snprintf(buf, 32, "Key pressed: %d", c);
	log_info(s, buf);

	if (is_ctrl_key(c))
	{
		editor_control_key(s, c);
	}
	else if (is_moving_key(c))
	{
		editor_move_cursor(s, c);
	}
}
