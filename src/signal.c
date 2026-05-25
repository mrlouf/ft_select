/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:38:30 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 13:42:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

static void	sig_kill(int signum)
{
	(void)signum;

	disable_raw_mode();
	exit(EXIT_SUCCESS);
}

static void	sig_resize(int signum)
{
	(void)signum;
}

static void	sig_suspend(int signum)
{
	(void)signum;
}

static void	sig_resume(int signum)
{
	(void)signum;
}

void	setup_signal_handlers()
{
	signal(SIGINT, sig_kill);
	signal(SIGKILL, sig_kill);
	signal(SIGQUIT, sig_kill);
	signal(SIGINT, sig_kill);
	signal(SIGABRT, sig_kill);
	signal(SIGFPE, sig_kill);
	signal(SIGILL, sig_kill);
	signal(SIGINT, sig_kill);
	signal(SIGSEGV, sig_kill);
	signal(SIGTERM, sig_kill);
	signal(SIGWINCH, sig_resize);
	signal(SIGTSTP, sig_suspend);
	signal(SIGCONT, sig_resume);
}
