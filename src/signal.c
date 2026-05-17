/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:38:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 16:44:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

static void	signal_handler_sigint(int signum)
{
	(void)signum;

	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	tputs(tgetstr("te", NULL), 1, ft_putchar);
	exit(EXIT_SUCCESS);
}

void	setup_signal_handlers(struct s_select *s)
{
	signal(SIGINT, signal_handler_sigint);
}
