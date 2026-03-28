/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:40:03 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 11:56:12 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

extern volatile sig_atomic_t	g_sig;
void	setup_signals_interactive(t_shell *sh);
void	setup_signals_exec_parent(void);
void	setup_signals_exec_child(void);
void	setup_signals_heredoc(t_shell *sh);
void	signals_reset_after_exec(t_shell *sh);
void	signals_apply_wait_status(t_shell *sh, int st, int is_last_cmd);
void	set_sa(int sig, void (*handler)(int), int flags);
void	sigint_heredoc_handler(int signo);
void	sigint_interactive_handler(int signo);

#endif
