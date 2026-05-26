/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:36:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 16:26:54 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_select.h"

void	tc_invert_colours(struct s_select *s)
{
	append_buffer(s, s->termcaps.mr, ft_strlen(s->termcaps.mr));
}

void	tc_reset_colours(struct s_select *s)
{
	append_buffer(s, s->termcaps.me, ft_strlen(s->termcaps.me));
}

void	tc_start_underline(struct s_select *s)
{
	append_buffer(s, "\E[4m", 4);
}

void	tc_stop_underline(struct s_select *s)
{
	append_buffer(s, "\E[24m", 5);
}
