/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/15 12:37:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void    tc_move_cursor(int x, int y)
{
    char buf[32];
    snprintf(buf, 32, "\x1b[%d;%dH", y + 1, x + 1);
    write(STDOUT_FILENO, buf, ft_strlen(buf));
}
