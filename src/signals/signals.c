/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:42:27 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 12:00:59 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

volatile sig_atomic_t	g_sig = 0;

void	sigint_interactive_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	set_sa(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(sig, &sa, NULL);
}

void	setup_signals_interactive(t_shell *sh)
{
	(void)sh;
	g_sig = 0;
	set_sa(SIGINT, sigint_interactive_handler, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_exec_parent(void)
{
	g_sig = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
