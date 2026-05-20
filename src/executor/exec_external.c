/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:22:40 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:22:50 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	print_cmd_not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static int	status_from_wait(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (1);
}

void	child_process(t_cmd *cmd, char **envp, char *path)
{
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	free(path);
	free_2d(envp);
	exit(126);
}

int	exec_external(t_shell *sh, t_cmd *cmd, char **envp, char *path)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(path),
			free_2d(envp), sh->last_status = 1, 1);
	if (pid == 0)
		child_process(cmd, envp, path);
	if (waitpid(pid, &wstatus, 0) == -1)
		return (perror("waitpid"), free(path),
			free_2d(envp), sh->last_status = 1, 1);
	return (free(path), free_2d(envp),
		sh->last_status = status_from_wait(wstatus), sh->last_status);
}
