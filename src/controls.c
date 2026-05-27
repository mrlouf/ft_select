/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:48:22 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/27 12:57:19 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

/* 
	This function set the n-th bit of the selected variable to 0,
	effectively deselecting the argument at index n.
	The left part (lower) keeps all bits below n, and the right part (upper)
	shifts all bits above n down by one to fill the gap.
*/
static u_int64_t	shift_selected_bits(u_int64_t bits, int n)
{
	u_int64_t	lower;
	u_int64_t	upper;

	lower = bits & ((1ULL << n) - 1);
	upper = bits >> (n + 1);
	return (lower | (upper << n));
}

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
	s->selected = shift_selected_bits(s->selected, i);
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
	s->selected ^= (1ULL << (s->cursor.y - 1));
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
		if (s->selected & (1ULL << i))
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
