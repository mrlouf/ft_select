/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:51:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 13:47:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

static void	handle_up_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (g_cursor.y > 0)
		g_cursor.y--;
	else
		g_cursor.y = s->ac - 1;

	if (g_cursor.x > (int)ft_strlen(s->av[g_cursor.y]) - 1)
		g_cursor.x = ft_strlen(s->av[g_cursor.y]) - 1;
}

static void handle_down_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (g_cursor.y < s->ac - 1)
		g_cursor.y++;
	else
		g_cursor.y = 0;

	if (g_cursor.x > (int)ft_strlen(s->av[g_cursor.y]) - 1)
		g_cursor.x = ft_strlen(s->av[g_cursor.y]) - 1;
}

static void	handle_right_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (g_cursor.x < g_win_size.ws_col - 1
		&& g_cursor.x < (int)ft_strlen(s->av[g_cursor.y]) - 1)
		g_cursor.x++;
}

static void	handle_left_key(struct s_select *s)
{
	if (s->ac == 0)
		return ;
	if (g_cursor.x > 0)
		g_cursor.x--;
}

void	editor_move_cursor(struct s_select *s, int key)
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
