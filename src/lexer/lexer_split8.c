/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:52:50 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/28 16:54:18 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

int	find_closing_quate(char *line, t_token_vars *vars, char c)
{
	vars->i++;
	vars->j = vars->i;
	while (line[vars->i] && line[vars->i] != c)
	{
		vars->i++;
	}
	if (!line[vars->i])
		return (1);
	return (0);
}

char	*handle_here_quate(char *str, char *line, t_token_vars *vars)
{
	char	*cut;
	char	c;

	c = line[vars->i];
	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
		return (NULL);
	str = ft_str_concat(str, cut);
	if (find_closing_quate(line, vars, c))
		return (free(str), NULL);
	cut = ft_str_cut(line, vars->j, vars->i);
	vars->j = vars->i + 1;
	str = ft_str_concat(str, cut);
	return (str);
}

char	*extract_eof(char *line, t_token_vars *vars)
{
	char	*str;
	char	*cut;

	str = NULL;
	vars->j = vars->i;
	while (line[vars->i] && !is_white_space(line[vars->i])
		&& line[vars->i] != '>' && line[vars->i] != '<'
		&& line[vars->i] != '|')
	{
		if (line[vars->i] == '"' || line[vars->i] == '\'')
		{
			str = handle_here_quate(str, line, vars);
			if (!str)
				return (NULL);
		}
		vars->i++;
	}
	cut = ft_str_cut(line, vars->j, vars->i);
	str = ft_str_concat(str, cut);
	printf("str is: %s\n", str);
	return (str);
}

t_token	*ft_check_first(t_token *head)
{
	if (head == NULL)
		return (head);
	if (head->type == TOK_PIPE)
	{
		free_token(head);
		return (NULL);
	}
	return (head);
}
