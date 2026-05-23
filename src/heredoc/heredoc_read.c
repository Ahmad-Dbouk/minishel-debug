/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:35:16 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/19 00:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

static int	write_heredoc_line(int fd, t_shell *sh, t_redir *r, char *str)
{
	char	*out;

	out = str;
	if (r->expand_heredoc)
	{
		out = expand_heredoc_line(sh, str);
		free(str);
		if (!out)
			return (1);
	}
	if (write(fd, out, ft_strlen(out)) < 0
		|| write(fd, "\n", 1) < 0)
	{
		free(out);
		return (1);
	}
	free(out);
	return (0);
}

int	prepare_heredocs(t_shell *sh, t_redir *r)
{
	int		pipe_fd[2];
	char	*str;

	if (!r || !r->target)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strcmp(str, r->target) == 0)
		{
			free(str);
			break ;
		}
		if (write_heredoc_line(pipe_fd[1], sh, r, str))
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			return (1);
		}
	}
	close(pipe_fd[1]);
	r->heredoc_fd = pipe_fd[0];
	return (0);
}

void	close_all_heredoc_fds(t_cmd *cmd)
{
	t_cmd	*c;
	t_redir	*r;

	c = cmd;
	while (c)
	{
		r = c->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC && r->heredoc_fd >= 0)
			{
				close(r->heredoc_fd);
				r->heredoc_fd = -1;
			}
			r = r->next;
		}
		c = c->next;
	}
}

int	loop_commands(t_cmd *cmd, t_shell *sh)
{
	t_cmd	*cur;
	t_redir	*tmp;

	cur = cmd;
	while (cur)
	{
		tmp = cur->redirs;
		while (tmp)
		{
			if (tmp->type == R_HEREDOC)
			{
				if (prepare_heredocs(sh, tmp))
				{
					close_all_heredoc_fds(cmd);
					return (1);
				}
			}
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	return (0);
}
