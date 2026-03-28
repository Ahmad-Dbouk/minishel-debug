/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:35:16 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 11:32:56 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_heredocs(t_redir *r, char **line)
{
	int		pipe_fd[2];
	char	*str;

	(void)line;
	if (!r || !r->target)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (modify_line (line, str))
			return (free(str), 1);
		if (ft_strcmp(str, r->target) == 0 || set_line(&str))
		{
			free(str);
			break ;
		}
		write_fd_free_str(str, pipe_fd);
	}
	set_fds(r, pipe_fd);
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

int	loop_commands(t_cmd *cmd, char **line)
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
				if (set_line(line) || prepare_heredocs(tmp, line))
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
