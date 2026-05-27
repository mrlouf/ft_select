/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:26:03 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/27 17:29:28 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_select.h"

void	tc_hide_cursor(struct s_select *s)
{
	append_buffer(s, s->termcaps.vi, ft_strlen(s->termcaps.vi));
}

void	tc_show_cursor(struct s_select *s)
{
	append_buffer(s, s->termcaps.ve, ft_strlen(s->termcaps.ve));
}

void	tc_move_cursor(struct s_select *s)
{
	char	*pos;

	pos = tgoto(s->termcaps.cm, s->cursor.x, s->cursor.y);
	append_buffer(s, pos, ft_strlen(pos));
}
