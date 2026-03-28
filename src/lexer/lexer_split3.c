/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:44:42 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/28 16:56:08 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

char	*ft_split_qoutation(char *line, char *str,
	t_shell *sh, t_token_vars *vars)
{
	char	*cut;
	char	*exp;

	while (line[vars->i] && line[vars->i] != '\"')
	{
		if (line[vars->i] == '$')
		{
			cut = ft_str_cut(line, vars->j, vars->i);
			if (!cut)
				return (free(str), NULL);
			str = ft_str_concat(str, cut);
			if (!str)
				return (NULL);
			vars->j = ++(vars->i);
			exp = ft_expand(line, &vars->i, &vars->j, sh);
			if (!exp)
				return (free(str), NULL);
			str = ft_str_concat(str, exp);
			if (!str)
				return (NULL);
		}
		else
			(vars->i)++;
	}
	return (ft_end_split(line, str, cut, vars));
}

const char	*toktype_to_str(t_toktype type)
{
	if (type == TOK_WORD)
		return ("WORD");
	if (type == TOK_PIPE)
		return ("PIPE");
	if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOK_APPEND)
		return ("APPEND");
	if (type == TOK_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("[%d] type=%s (%d)", i, toktype_to_str(head->type), head->type);
		if (head->value)
			printf(" value=\"%s\"", head->value);
		printf("\n");
		head = head->next;
		i++;
	}
}

t_token	*init_token(char *line, t_shell *sh)
{
	t_token	*head;

	head = NULL;
	head = ft_split_line(line, sh, head);
	head = ft_verify_tokens(head);
	head = ft_check_first(head);
	return (head);
}
