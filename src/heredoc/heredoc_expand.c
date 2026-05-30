/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/19 00:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static char	*append_segment(char *str, char *line, int start, int end)
{
	char	*cut;

	cut = ft_str_cut(line, start, end);
	if (!cut)
		return (free(str), NULL);
	str = ft_str_concat(str, cut);
	return (str);
}

static char	*expand_dollar(char *str, char *line, t_token_vars *vars,
		t_shell *sh)
{
	t_expand_ctx	ctx;
	char			*exp;

	str = append_segment(str, line, vars->j, vars->i);
	if (!str)
		return (NULL);
	ctx.i = vars->i + 1;
	ctx.j = ctx.i;
	ctx.inside_dquotes = 1;
	exp = ft_expand(line, sh, &ctx);
	if (!exp)
		return (free(str), NULL);
	vars->i = ctx.i;
	vars->j = ctx.i;
	str = ft_str_concat(str, exp);
	return (str);
}

char	*expand_heredoc_line(t_shell *sh, char *line)
{
	char			*str;
	t_token_vars	vars;

	str = NULL;
	vars.i = 0;
	vars.j = 0;
	while (line[vars.i])
	{
		if (line[vars.i] == '$')
		{
			str = expand_dollar(str, line, &vars, sh);
			if (!str)
				return (NULL);
		}
		else
			vars.i++;
	}
	return (append_segment(str, line, vars.j, vars.i));
}
