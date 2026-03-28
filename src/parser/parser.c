/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:30:16 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/28 17:01:54 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	handle_word_token(t_parse_ctx *ctx, t_token *cur)
{
	t_word	*new_word;

	new_word = word_new(cur->value);
	if (!new_word)
	{
		free_parser(ctx->token, ctx->cmd, ctx->words);
		free_cmds(ctx->new_cmd);
		return (1);
	}
	ctx->words = insert_word_at_tail(ctx->words, new_word);
	return (0);
}

int	finalize_last_cmd(t_parse_ctx *ctx)
{
	if (ctx->words)
	{
		ctx->new_cmd->argv = convert_to_argv(ctx->words);
		if (!ctx->new_cmd->argv)
			return (free_cmds(ctx->new_cmd),
				free_parser(ctx->token, ctx->cmd, ctx->words), 1);
	}
	else
	{
		ctx->new_cmd->argv = alloc_null_args();
		if (!ctx->new_cmd->argv)
			return (free_parser(ctx->token, ctx->cmd, ctx->words),
				free_cmds(ctx->new_cmd), 1);
	}
	ctx->cmd = insert_cmd_at_tail(ctx->cmd, ctx->new_cmd);
	return (0);
}

int	handle_current_token(t_parse_ctx *ctx, t_token **cur)
{
	if ((*cur)->type == TOK_PIPE)
	{
		if (handle_pipe_token(ctx))
			return (1);
	}
	else if (is_redir_token((*cur)->type))
	{
		if (handle_redir_token(ctx, cur))
			return (1);
	}
	else
	{
		if (handle_word_token(ctx, *cur))
			return (1);
	}
	*cur = (*cur)->next;
	return (0);
}

t_cmd	*parse_token(t_token *token)
{
	t_parse_ctx	ctx;
	t_token		*cur;

	if (!token)
		return (NULL);
	ctx.token = token;
	ctx.words = NULL;
	cur = ctx.token;
	if (init_cmd(&ctx.new_cmd, &ctx.cmd))
		return (free_token(ctx.token), NULL);
	while (cur)
	{
		if (handle_current_token(&ctx, &cur))
			return (NULL);
	}
	if (finalize_last_cmd(&ctx))
		return (NULL);
	return (free_words(ctx.words), free_token(ctx.token), ctx.cmd);
}
