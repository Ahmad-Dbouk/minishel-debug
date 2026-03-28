/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:47:57 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:30:19 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "parser.h"
# include "exec.h"

typedef struct s_execution_vars
{
	int			n;
	pid_t		*pids;
	int			i;
	int			prev_read;
	int			pipefd[2];
	pid_t		pid;
	pid_t		last_pid;
	t_cmd		*cur;
	int			error_happened;
	t_stdio_bak	back;
}	t_execution_vars;

int		count_cmds(t_cmd *cmds);
int		is_builtin_cmd(t_cmd *cmd);
int		status_to_exitcode(int status);
int		child_exec(t_shell *sh, t_cmd *cmd);
int		run_builtin(t_shell *sh, t_cmd *cmds, int interactive);
int		child_apply_redirs(t_shell *sh, t_cmd *cmd);
int		exec_end(t_shell *sh, t_execution_vars *vars);
int		wait_pipeline(pid_t *pids, int n, pid_t last_pid);
int		run_one_builtin(t_shell *sh, t_cmd *cmds,
			t_execution_vars *vars, int interactive);
int		exec_export(t_shell *sh, t_cmd *cmd);
int		is_valid_export_arg(const char *arg);
int		exec_unset(t_shell *sh, t_cmd *cmd);
int		export_assign(t_shell *sh, const char *arg);
int		export_assign_helper(t_shell *sh, const char *arg,
			char *key, char *val);

void	close_safe(int fd);
void	set_vars_pipefd(t_execution_vars *vars);
void	init_vars(t_execution_vars *vars, t_cmd *cmds);
void	handle_vars_next(t_execution_vars *vars);
void	child_setup_pipe_fds(int prev_read, int pipefd[2], int is_last);

#endif