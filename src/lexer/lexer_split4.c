/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:48:18 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/27 16:53:26 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

t_token	*handle_pipe(char *str, char *line, t_token *head, t_token_vars *vars)
{
	str = ft_str_cut(line, vars->i, vars->i + 1);
	if (str)
	{
		head = insert_at_tail(head, str, get_toktype(str));
		if (!head)
			return (NULL);
	}
	else
	{
		free_token(head);
		return (NULL);
	}
	vars->i++;
	return (head);
}

t_token	*handle_heredoc(char *str, char *line,
	t_token *head, t_token_vars *vars)
{
	str = ft_str_cut(line, vars->i - 1, vars->i + 1);
	vars->i++;
	while (line[vars->i] && is_white_space(line[vars->i]))
		vars->i++;
	if (!str || !line[vars->i])
		return (free_token(head), NULL);
	head = insert_at_tail(head, str, get_toktype(str));
	if (!head)
		return (NULL);
	str = extract_eof(line, vars);
	if (!str)
		return (free_token(head), NULL);
	head = insert_at_tail(head, str, get_toktype(str));
	return (head);
}

t_token	*handle_input_redirection(char *str, char *line,
	t_token *head, t_token_vars *vars)
{
	vars->i++;
	if (line [vars->i] && line[vars->i] == '<')
		return (handle_heredoc (str, line, head, vars));
	else
	{
		str = ft_str_cut(line, vars->i - 1, vars->i);
		if (str)
		{
			head = insert_at_tail(head, str, get_toktype(str));
			if (!head)
				return (NULL);
		}
		else
		{
			free_token(head);
			return (NULL);
		}
	}
	return (head);
}

t_token	*handle_append(char *str, char *line,
	t_token *head, t_token_vars *vars)
{
	str = ft_str_cut(line, vars->i - 1, vars->i + 1);
	vars->i++;
	if (str)
	{
		head = insert_at_tail(head, str, get_toktype(str));
		if (!head)
			return (NULL);
	}
	else
	{
		free_token(head);
		return (NULL);
	}
	return (head);
}

t_token	*handle_output_redirection(char *str, char *line,
	t_token *head, t_token_vars *vars)
{
	vars->i++;
	if (line [vars->i] && line[vars->i] == '>')
		return (handle_append (str, line, head, vars));
	else
	{
		str = ft_str_cut(line, vars->i - 1, vars->i);
		if (str)
		{
			head = insert_at_tail(head, str, get_toktype(str));
			if (!head)
				return (NULL);
		}
		else
		{
			free_token(head);
			return (NULL);
		}
	}
	return (head);
}
