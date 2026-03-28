/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:02:11 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 16:08:46 by adbouk           ###   ########.fr       */
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

void	close_safe(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	count_cmds(t_cmd *cmds)
{
	int	n;

	n = 0;
	while (cmds)
	{
		n++;
		cmds = cmds->next;
	}
	return (n);
}

int	status_to_exitcode(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	child_setup_pipe_fds(int prev_read, int pipefd[2], int is_last)
{
	if (prev_read != -1)
	{
		if (dup2(prev_read, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (!is_last)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	close_safe(prev_read);
	close_safe(pipefd[0]);
	close_safe(pipefd[1]);
}

int	child_apply_redirs(t_shell *sh, t_cmd *cmd)
{
	apply_redirs(sh, cmd);
	return (0);
}
