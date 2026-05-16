/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:26:33 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:56:31 by arahal           ###   ########.fr       */
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

void	handel_pid_fail(t_execution_vars *vars)
{
	perror("fork");
	vars->error_happened = 1;
	close_safe(vars->pipefd[0]);
	close_safe(vars->pipefd[1]);
}

void	handle_pipe_fail(t_execution_vars *vars)
{
	perror("pipe");
	vars->error_happened = 1;
}

void	process_child_pid(t_shell *sh, t_execution_vars *vars)
{
	child_setup_pipe_fds(vars->prev_read,
		vars->pipefd, (vars->cur->next == NULL));
	if (apply_redirs(sh, vars->cur) != 0)
		exit(1);
	if (is_builtin_cmd(vars->cur))
		exit(run_builtin(sh, vars->cur, 0));
	child_exec(sh, vars->cur);
}

int	process_commands(t_shell *sh, t_execution_vars *vars)
{
	while (vars->cur)
	{
		set_vars_pipefd (vars);
		if (vars->cur->next)
		{
			if (pipe(vars->pipefd) == -1)
			{
				handle_pipe_fail (vars);
				break ;
			}
		}
		vars->pid = fork();
		if (vars->pid == -1)
		{
			handel_pid_fail (vars);
			break ;
		}
		if (vars->pid == 0)
			process_child_pid (sh, vars);
		handle_vars_next(vars);
	}
	return (exec_end (sh, vars));
}

int	exec_pipeline(t_shell *sh, t_cmd *cmds, int interactive)
{
	t_execution_vars	vars;

	vars.n = count_cmds(cmds);
	if (vars.n == 0)
		return (0);
	if (vars.n == 1 && is_builtin_cmd (cmds))
		return (run_one_builtin (sh, cmds, &vars, interactive));
	vars.pids = malloc(sizeof(pid_t) * vars.n);
	if (!vars.pids)
		return (perror("minishell"), sh->last_status = 1, 1);
	init_vars (&vars, cmds);
	return (process_commands (sh, &vars));
}
