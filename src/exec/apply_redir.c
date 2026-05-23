/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:25:46 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 19:33:18 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_redir_file(t_redir *r)
{
	if (r->type == R_IN)
		return (open(r->target, O_RDONLY));
	if (r->type == R_OUT)
		return (open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (r->type == R_APPEND)
		return (open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (-1);
}

int	redir_dup_to_fd(int fd, t_redir *r)
{
	int	target;

	if (r->type == R_IN)
		target = STDIN_FILENO;
	else if (r->type == R_OUT || r->type == R_APPEND)
		target = STDOUT_FILENO;
	else
		return (-1);
	return (dup2(fd, target));
}

int	set_heredoc_redir(t_shell *sh, t_redir *r)
{
	if (r->heredoc_fd < 0)
	{
		sh->last_status = 1;
		return (1);
	}
	if (dup2(r->heredoc_fd, STDIN_FILENO) < 0)
	{
		close(r->heredoc_fd);
		r->heredoc_fd = -1;
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		sh->last_status = 1;
		return (1);
	}
	close(r->heredoc_fd);
	r->heredoc_fd = -1;
	return (0);
}

int	apply_single_redir(t_shell *sh, t_redir *r)
{
	int	fd;

	if (r->type == R_HEREDOC)
		return (set_heredoc_redir(sh, r));
	fd = open_redir_file(r);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(r->target);
		sh->last_status = 1;
		return (1);
	}
	if (redir_dup_to_fd(fd, r) < 0)
	{
		close (fd);
		ft_putstr_fd("minishell: ", 2);
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_redirs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*cur_r;

	if (!cmd)
		return (1);
	cur_r = cmd->redirs;
	while (cur_r)
	{
		if (apply_single_redir(shell, cur_r))
			return (1);
		cur_r = cur_r->next;
	}
	return (0);
}
