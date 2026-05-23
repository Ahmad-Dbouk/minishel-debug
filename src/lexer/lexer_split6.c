/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:58:52 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 20:58:21 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

static t_token	*insert_split_word(char *str, t_token *head, t_shell *sh)
{
	char	**fields;

	fields = split_word_ifs(str, sh);
	free(str);
	if (!fields)
		return (free_token(head), NULL);
	if (!fields[0])
		return (free(fields), head);
	if (!fields[1])
	{
		head = insert_at_tail(head, fields[0], TOK_WORD);
		free(fields);
		if (!head)
			return (NULL);
		return (head);
	}
	return (insert_fields_at_tail(head, fields));
}

t_token	*insert_no_qaute(char *str, char *line,
	t_token *head, t_shell *sh, t_token_vars *vars)
{
	char	*cut;

	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
	{
		if (str)
			free(str);
		free_token(head);
		return (NULL);
	}
	str = ft_str_concat(str, cut);
	if (!str)
		return (free_token(head), NULL);
	if (vars->split_fields)
	{
		head = insert_split_word(str, head, sh);
		if (!head)
			return (NULL);
		return (head);
	}
	head = insert_at_tail(head, str, TOK_WORD);
	if (!head)
		return (NULL);
	return (head);
}

char	*handle_no_qaute(char *str, char *line,
	t_shell *sh, t_token_vars *vars)
{
	if (line [vars->i] && line[vars->i] == '\'')
	{
		vars->split_fields = 0;
		str = handle_single_quote (str, line, vars);
		if (!str)
			return (NULL);
	}
	if (line [vars->i] && line[vars->i] == '\"')
	{
		vars->split_fields = 0;
		str = handle_double_quote (str, line, sh, vars);
		if (!str)
			return (NULL);
	}
	if (line [vars->i] && line[vars->i] == '$')
	{
		str = handle_dollar_no_qautation(str, line, sh, vars);
		if (!str)
			return (NULL);
	}
	return (str);
}
