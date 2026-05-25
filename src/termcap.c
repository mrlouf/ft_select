/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 14:11:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	tc_move_cursor(struct s_select *s)
{
	char	*pos;

	pos = tgoto(s->termcaps.cm, g_cursor.x, g_cursor.y);
	tputs(pos, 1, ft_putchar);
}

void	tc_clear_screen(void)
{
	char	*cl;

	cl = tgetstr("cl", NULL);
	tputs(cl, 1, ft_putchar);
}
