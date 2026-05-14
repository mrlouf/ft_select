/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:54:14 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 21:31:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	editor_draw_arguments(char **args, int count, struct s_select *s)
{
	(void)args;
	(void)count;
	/* 
	int	i;

	(void)args;
	i = 0;
	while (i < s->win_size.ws_row - 1 && i < count)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		ft_putstr_fd("\r\n", STDOUT_FILENO);
		i++;
	} */

	for (int i = 0; i < s->win_size.ws_row - 1; i++)
	{
		for (int j = 0; j < s->win_size.ws_col - 1; j++)
		{
			append_buffer(s, "*", 1);
		}
		append_buffer(s, "\r\n", 2);
	}
	write_buffer(s->buf);
}

void	editor_refresh_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}
