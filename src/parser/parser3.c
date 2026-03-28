/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:05:14 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 20:39:30 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tmp2;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_cmd_args(tmp->argv);
		while (tmp->redirs)
		{
			tmp2 = tmp->redirs;
			tmp->redirs = tmp->redirs->next;
			free(tmp2->target);
			if (tmp2->heredoc_fd != -1)
				close(tmp2->heredoc_fd);
			free(tmp2);
		}
		free(tmp);
	}
}

void	free_argv(char **argv, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free (argv[i]);
		i++;
	}
	free(argv);
}

char	**convert_to_argv(t_word *words)
{
	int		argc;
	char	**argv;
	t_word	*cur;
	int		i;

	argc = -1;
	cur = words;
	while (argc++, cur)
		cur = cur->next;
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	cur = words;
	i = -1;
	while (i++, i < argc)
	{
		argv[i] = ft_strdup(cur->str);
		if (!argv[i])
			return (free_argv(argv, i), NULL);
		cur = cur->next;
	}
	argv[argc] = NULL;
	return (argv);
}

t_cmd	*insert_cmd_at_tail(t_cmd *cmd, t_cmd *new_cmd)
{
	t_cmd	*cur;

	if (!cmd)
		return (new_cmd);
	cur = cmd;
	while (cur->next)
		cur = cur->next;
	cur->next = new_cmd;
	return (cmd);
}

int	init_new_cmd(t_cmd **new_cmd)
{
	*new_cmd = malloc (sizeof(t_cmd));
	if (!*new_cmd)
		return (1);
	(*new_cmd)->argv = NULL;
	(*new_cmd)->next = NULL;
	(*new_cmd)->redirs = NULL;
	return (0);
}
