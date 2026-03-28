/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:27:06 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:47:42 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../../includes/execution.h"

int	run_one_builtin(t_shell *sh, t_cmd *cmds, t_execution_vars *vars,
		int interactive)
{
	if (stdio_backup (&vars->back))
		return (perror("minishell"), sh->last_status = 1, 1);
	if (apply_redirs(sh, cmds) != 0)
	{
		stdio_restore(&vars->back);
		sh->last_status = 1;
		return (1);
	}
	sh->last_status = run_builtin(sh, cmds, interactive);
	stdio_restore(&vars->back);
	return (sh->last_status);
}

void	init_vars(t_execution_vars *vars, t_cmd *cmds)
{
	vars->i = 0;
	vars->prev_read = -1;
	vars->last_pid = -1;
	vars->cur = cmds;
	vars->error_happened = 0;
}

void	handle_vars_next(t_execution_vars *vars)
{
	vars->pids[vars->i++] = vars->pid;
	vars->last_pid = vars->pid;
	close_safe(vars->prev_read);
	close_safe(vars->pipefd[1]);
	vars->prev_read = vars->pipefd[0];
	vars->cur = vars->cur->next;
}

void	set_vars_pipefd(t_execution_vars *vars)
{
	vars->pipefd[0] = -1;
	vars->pipefd[1] = -1;
}

int	exec_end(t_shell *sh, t_execution_vars *vars)
{
	close_safe(vars->prev_read);
	sh->last_status = wait_pipeline(vars->pids, vars->i, vars->last_pid);
	if (vars->error_happened && sh->last_status == 0)
		sh->last_status = 1;
	free(vars->pids);
	return (sh->last_status);
}
