/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/15 12:45:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	tc_move_cursor(int x, int y)
{
    char *cm;

    cm = tgetstr("cm", NULL);
    tputs(tgoto(cm, x, y), 1, ft_putchar);
}

void	tc_clear_screen(void)
{
	char *cl;

	cl = tgetstr("cl", NULL);
	tputs(cl, 1, ft_putchar);
}
