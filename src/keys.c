/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:43:28 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/15 10:38:28 by nicolas          ###   ########.fr       */
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

	nread = 0;
	while (nread != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			fatal_error("read failed", s);
		nread = read(STDIN_FILENO, &c, 1);
	}
	return (c);
}

void	editor_process_keypress(struct s_select *s)
{
	char	c;

	c = editor_read_key(s);
	log_info(s, "Key pressed");
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
