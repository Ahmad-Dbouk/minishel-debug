/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:53:15 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/28 16:19:39 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*handle_special_char(char *str, char *line,
	t_token *head, t_token_vars *vars)
{
	if (line[vars->i] && line[vars->i] == '|')
	{
		head = handle_pipe (str, line, head, vars);
		if (!head)
			return (NULL);
	}
	if (line [vars->i] && line[vars->i] == '<')
	{
		head = handle_input_redirection (str, line, head, vars);
		if (!head)
			return (NULL);
	}
	if (line [vars->i] && line[vars->i] == '>')
	{
		head = handle_output_redirection(str, line, head, vars);
		if (!head)
			return (NULL);
	}
	return (head);
}

int	is_word_char(char *line, t_token_vars vars)
{
	if (line[vars.i] && line[vars.i] != '|' && line[vars.i] != '<'
		&& line[vars.i] != '>' && !is_white_space(line[vars.i]))
		return (1);
	return (0);
}

void	set_str_i_j(char **str, t_token_vars *vars)
{
	*str = NULL;
	vars->j = vars->i;
}

int	check(char *line, t_token_vars *vars)
{
	return (line[vars->i] == '\'' || line[vars->i] == '"'
		|| line[vars->i] == '$');
}

t_token	*ft_verify_tokens(t_token *head)
{
	t_token	*cur;

	cur = head;
	if (cur)
	{
		if (cur->type == TOK_PIPE)
			return (free_token(head), NULL);
	}
	while (cur)
	{
		if (cur->type == TOK_PIPE)
		{
			if ((cur->next && cur->next->type == TOK_PIPE) || !cur->next)
				return (free_token(head), NULL);
		}
		if (cur->type == TOK_APPEND || cur->type == TOK_HEREDOC
			|| cur->type == TOK_REDIR_IN
			|| cur->type == TOK_REDIR_OUT)
		{
			if ((cur->next && cur->next->type != TOK_WORD) || !cur->next)
				return (free_token(head), NULL);
		}
		cur = cur->next;
	}
	return (head);
}
