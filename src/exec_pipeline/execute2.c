/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:07:24 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:11:08 by arahal           ###   ########.fr       */
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

int	child_exec(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**envp;

	if (!cmd->argv || !cmd->argv[0])
		exit(1);
	path = resolve_cmd_path(sh, cmd->argv[0], &sh->last_status);
	if (!path)
		return (sh->last_status);
	envp = env_to_envp(sh);
	if (!envp)
		return (free(path), sh->last_status = 1, 1);
	child_process(cmd, envp, path);
	exit(1);
	return (0);
}

int	wait_pipeline(pid_t *pids, int n, pid_t last_pid)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	w;

	i = 0;
	status = 0;
	last_status = 0;
	while (i < n)
	{
		w = waitpid(pids[i], &status, 0);
		while (w == -1 && errno == EINTR)
			w = waitpid(pids[i], &status, 0);
		if (w == -1)
		{
			perror("waitpid");
			i++;
			continue ;
		}
		if (w == last_pid)
			last_status = status;
		i++;
	}
	return (status_to_exitcode(last_status));
}

int	is_builtin_cmd(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin(t_shell *sh, t_cmd *cmds, int interactive)
{
	if (ft_strcmp(cmds->argv[0], "echo") == 0)
		return (exec_echo(cmds, 0, 1));
	if (ft_strcmp(cmds->argv[0], "cd") == 0)
		return (exec_cd(sh, cmds, NULL, NULL));
	if (ft_strcmp(cmds->argv[0], "pwd") == 0)
		return (exec_pwd(cmds));
	if (ft_strcmp(cmds->argv[0], "export") == 0)
		return (exec_export(sh, cmds));
	if (ft_strcmp(cmds->argv[0], "unset") == 0)
		return (exec_unset(sh, cmds));
	if (ft_strcmp(cmds->argv[0], "env") == 0)
		return (exec_env(sh, cmds));
	if (ft_strcmp(cmds->argv[0], "exit") == 0)
		return (exec_exit(sh, cmds, interactive));
	return (1);
}
