/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:51:20 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 14:57:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	handle_up_key(struct s_select *s)
{
	if (s->cursor.y > 0)
		s->cursor.y--;
	else
		s->cursor.y = s->ac - 1;

    if (s->cursor.x > (int)ft_strlen(s->av[s->cursor.y]) - 1)
        s->cursor.x = ft_strlen(s->av[s->cursor.y]) - 1;
}

void	handle_down_key(struct s_select *s)
{
	if (s->cursor.y < s->ac - 1)
		s->cursor.y++;
	else
		s->cursor.y = 0;

    if (s->cursor.x > (int)ft_strlen(s->av[s->cursor.y]) - 1)
        s->cursor.x = ft_strlen(s->av[s->cursor.y]) - 1;
}

void    handle_right_key(struct s_select *s)
{
    if (s->cursor.x < s->win_size.ws_col - 1
        && s->cursor.x < (int)ft_strlen(s->av[s->cursor.y]) - 1)
        s->cursor.x++;
}

void    handle_left_key(struct s_select *s)
{
    if (s->cursor.x > 0)
        s->cursor.x--;
}