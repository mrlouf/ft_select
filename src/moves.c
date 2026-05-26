/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:51:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 17:06:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	handle_up_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (s->cursor.y > 1 && s->cursor.y <= s->ac)
		s->cursor.y--;
	else
		s->cursor.y = s->ac;
	if (s->cursor.x > (int)ft_strlen(s->av[s->cursor.y - 1]) - 1 + TILDE_OFFSET)
		s->cursor.x = ft_strlen(s->av[s->cursor.y - 1]) - 1 + TILDE_OFFSET;
}

static void	handle_down_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (s->cursor.y < s->ac )
		s->cursor.y++;
	else
		s->cursor.y = 1;
	if (s->cursor.x > (int)ft_strlen(s->av[s->cursor.y - 1]) - 1 + TILDE_OFFSET)
		s->cursor.x = ft_strlen(s->av[s->cursor.y - 1]) - 1 + TILDE_OFFSET;
}

static void	handle_right_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (s->cursor.x < s->win_size.ws_col - 1
		&& s->cursor.x < (int)ft_strlen(s->av[s->cursor.y - 1]) - 1 + TILDE_OFFSET)
		s->cursor.x++;
}

static void	handle_left_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (s->cursor.x > TILDE_OFFSET)
		s->cursor.x--;
}

void	move_cursor(struct s_select *s, int key)
{
	if (key == KEY_UP)
		handle_up_key(s);
	else if (key == KEY_DOWN)
		handle_down_key(s);
	else if (key == KEY_LEFT)
		handle_left_key(s);
	else if (key == KEY_RIGHT)
		handle_right_key(s);
}
