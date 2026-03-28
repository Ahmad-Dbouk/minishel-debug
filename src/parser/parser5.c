/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:12:28 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/27 13:12:30 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_argv2(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd_one(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_argv2(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

void	free_cmds2(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_cmd_one(cmd);
		cmd = next;
	}
}

void	free_parser(t_token *token, t_cmd *cmd, t_word *words)
{
	free_token(token);
	free_words(words);
	free_cmds(cmd);
}

char	**alloc_null_args(void)
{
	char	**args;

	args = malloc(1 * (sizeof(char *)));
	if (!args)
		return (NULL);
	args[0] = NULL;
	return (args);
}
