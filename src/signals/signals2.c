/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:52:27 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 11:57:08 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

void	setup_signals_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_heredoc(t_shell *sh)
{
	(void)sh;
	g_sig = 0;
	set_sa(SIGINT, sigint_heredoc_handler, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_reset_after_exec(t_shell *sh)
{
	setup_signals_interactive(sh);
}

void	signals_apply_wait_status(t_shell *sh, int st, int is_last_cmd)
{
	int	sig;

	if (!is_last_cmd)
		return ;
	if (WIFEXITED(st))
	{
		sh->last_status = WEXITSTATUS(st);
		return ;
	}
	if (WIFSIGNALED(st))
	{
		sig = WTERMSIG(st);
		sh->last_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
}
