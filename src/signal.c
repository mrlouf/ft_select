/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:38:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/28 11:21:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	sig_kill(int signum)
{
	(void)signum;
	disable_raw_mode();
	ft_putstr_fd("Exiting ft_select: signal received: ", STDERR_FILENO);
	ft_putnbr_fd(signum, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

static void	sig_resize(int signum)
{
	(void)signum;
}

static void	sig_suspend(int signum)
{
	(void)signum;
	disable_raw_mode();
	signal(SIGTSTP, SIG_DFL);
	raise(SIGTSTP);
}

static void	sig_resume(int signum)
{
	(void)signum;
	enable_raw_mode();
	setup_signal_handlers();
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sig_kill);
	signal(SIGQUIT, sig_kill);
	signal(SIGABRT, sig_kill);
	signal(SIGTERM, sig_kill);
	signal(SIGWINCH, sig_resize);
	signal(SIGCONT, sig_resume);
	signal(SIGTSTP, sig_suspend);
}
