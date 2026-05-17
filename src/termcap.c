/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 14:46:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	tc_move_cursor(struct s_select *s)
{
    tputs(tgoto(s->termcaps.cm, s->cursor.x, s->cursor.y), 1, ft_putchar);
}

void	tc_clear_screen(void)
{
	char *cl;

	cl = tgetstr("cl", NULL);
	tputs(cl, 1, ft_putchar);
}
