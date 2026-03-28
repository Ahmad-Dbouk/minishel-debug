/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   loop.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/01/05 09:34:03 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/23 18:46:21 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"
// in this function i have just changed not checking if it is interactive
// to be able to take lines as input (not interactice mode)
void	handle_interactive_line(t_loop_ctx *ctx)
{
	if (!ctx->line || ctx->line[0] == '\0')
		return ;
	ctx->head = NULL;
	ctx->head = init_token(ctx->line, &ctx->sh);
	if (!ctx->head)
	{
		ctx->sh.last_status = 2;
		return ;
	}
	ctx->p = parse_token(ctx->head);
	if (!ctx->p)
	{
		ctx->sh.last_status = 2;
		return (free_token(ctx->head));
	}
	if (ctx->interactive)
		add_history(ctx->line);
	if (loop_commands(ctx->p))
		return (free_token (ctx->head), free_cmds (ctx->p));
	exec_pipeline(&ctx->sh, ctx->p, ctx->interactive);
	free_cmds(ctx->p);
}

int	ms_loop(char **envp)
{
	t_loop_ctx	ctx;

	if (env_init_from_envp(&ctx.sh, envp) == -1)
		return (1);
	ctx.interactive = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ctx.interactive = 1;
	while (1)
	{
		if (ctx.interactive)
			ctx.line = readline("minishell$ ");
		else
			ctx.line = ms_read_stdin_line(0, 64, 0);
		if (!ctx.line)
		{
			if (ctx.interactive)
				printf("exit\n");
			break ;
		}
		handle_interactive_line(&ctx);
		free(ctx.line);
	}
	if (ctx.interactive)
		rl_clear_history();
	return (env_clear(&ctx.sh.env), 0);
}
