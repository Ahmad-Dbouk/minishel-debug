/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:22:57 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 21:23:21 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	set_cmd_argv_on_pipe(t_word **words, t_cmd *new_cmd,
	t_token *token, t_cmd *cmd)
{
	if (*words)
	{
		new_cmd->argv = convert_to_argv(*words);
		if (!new_cmd->argv)
			return (free_cmds(new_cmd), free_parser(token, cmd, *words), 1);
		free_words(*words);
		*words = NULL;
	}
	else
	{
		new_cmd->argv = alloc_null_args();
		if (!new_cmd->argv)
		{
			free_parser(token, cmd, *words);
			free_cmds(new_cmd);
			return (1);
		}
	}
	return (0);
}

int	set_cmd_argv(t_word **words, t_cmd *new_cmd,
	t_token *token, t_cmd *cmd)
{
	if (*words)
	{
		new_cmd->argv = convert_to_argv(*words);
		if (!new_cmd->argv)
			return (free_cmds(new_cmd), free_parser(token, cmd, *words), 1);
	}
	else
	{
		new_cmd->argv = alloc_null_args();
		if (!new_cmd->argv)
			return (free_parser(token, cmd, *words), free_cmds(new_cmd), 1);
	}
	return (0);
}

int	insert_cmd_on_pipe(t_cmd *new_cmd, t_word **words,
	t_token *token, t_cmd *cmd)
{
	if (set_cmd_argv_on_pipe (words, new_cmd, token, cmd))
		return (1);
	cmd = insert_cmd_at_tail(cmd, new_cmd);
	if (init_new_cmd(&new_cmd))
		return (free_parser(token, cmd, *words), 1);
	return (0);
}

int	handle_pipe_token(t_parse_ctx *ctx)
{
	if (ctx->words)
	{
		ctx->new_cmd->argv = convert_to_argv(ctx->words);
		if (!ctx->new_cmd->argv)
			return (free_cmds(ctx->new_cmd),
				free_parser(ctx->token, ctx->cmd, ctx->words), 1);
		free_words(ctx->words);
		ctx->words = NULL;
	}
	else
	{
		ctx->new_cmd->argv = alloc_null_args();
		if (!ctx->new_cmd->argv)
			return (free_parser(ctx->token, ctx->cmd, ctx->words),
				free_cmds(ctx->new_cmd), 1);
	}
	ctx->cmd = insert_cmd_at_tail(ctx->cmd, ctx->new_cmd);
	if (init_new_cmd(&ctx->new_cmd))
		return (free_parser(ctx->token, ctx->cmd, ctx->words), 1);
	return (0);
}

int	handle_redir_token(t_parse_ctx *ctx, t_token **cur)
{
	t_redir	*redir;

	redir = redir_new(return_redir_type((*cur)->type), (*cur)->next->value);
	if (!redir)
	{
		free_parser(ctx->token, ctx->cmd, ctx->words);
		free_cmds(ctx->new_cmd);
		return (1);
	}
	ctx->new_cmd->redirs = insert_redir_at_tail(ctx->new_cmd->redirs, redir);
	*cur = (*cur)->next;
	return (0);
}
