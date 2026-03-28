/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:26:01 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 11:27:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_line(char **line)
{
	char	*str1;
	char	*str2;

	str1 = "\n";
	str2 = ft_strjoin(*line, str1);
	if (!str2)
		return (1);
	free (*line);
	*line = str2;
	return (0);
}

void	write_fd_free_str(char *str, int *pipe_fd)
{
	write(pipe_fd[1], str, ft_strlen(str));
	free(str);
}

void	set_fds(t_redir *r, int *pipe_fd)
{
	close(pipe_fd[1]);
	r->heredoc_fd = pipe_fd[0];
}

int	modify_line(char **line, char *str)
{
	char	*s;
	char	*s1;

	s = ft_strjoin(str, "\n");
	if (!s)
		return (1);
	s1 = ft_strjoin(*line, s);
	free(s);
	if (!s1)
		return (1);
	free (*line);
	*line = s1;
	return (0);
}
