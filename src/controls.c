/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:48:22 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 18:38:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

/* 
	Deletes the currently selected argument from the list,
	and shifts the remaining arguments up. No free since we are still
	using the original argv pointers ie. working on the stack.
	If there are no more arguments left after deletion,
	the program exits gracefully.
*/
static void	delete_current_argument(struct s_select *s)
{
	int	i;

	if (s->ac == 0)
		return ;
	if (s->ac == 1)
	{
		disable_raw_mode();
		exit(EXIT_SUCCESS);
	}
	i = s->cursor.y - 1;
	while (i < s->ac)
	{
		s->av[i] = s->av[i + 1];
		i++;
	}
	s->ac--;
}

static void	select_argument(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	s->selected ^= (1 << (s->cursor.y - 1));
	if (s->cursor.y < s->ac)
		s->cursor.y++;
	else
		s->cursor.y = 1;
	s->cursor.x = TILDE_OFFSET;
}

static void	send_selected_arguments_to_stdout(struct s_select *s)
{
	int	i;
	int	first;

	i = 0;
	first = 1;
	while (i < s->ac)
	{
		if (s->selected & (1 << i))
		{
			if (!first)
				ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(s->av[i], STDOUT_FILENO);
			first = 0;
		}
		i++;
	}
}

void	control_key(struct s_select *s, int key)
{
	if (key == KEY_ESCAPE)
	{
		disable_raw_mode();
		log_info(s, "Exiting program");
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_SPACE)
	{
		select_argument(s);
		log_info(s, "Space key pressed");
	}
	else if (key == KEY_ENTER)
	{
		send_selected_arguments_to_stdout(s);
		disable_raw_mode();
		log_info(s, "Enter key pressed");
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_BACKSPACE || key == KEY_DELETE)
	{
		delete_current_argument(s);
		log_info(s, "Delete key pressed");
	}
}
