/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:56:31 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/27 19:55:49 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

char	*return_malloc_fail(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*handle_single_quote(char *str, char *line, t_token_vars *vars)
{
	char	*cut;

	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
		return (return_malloc_fail (str));
	str = ft_str_concat(str, cut);
	if (!str)
		return (NULL);
	vars->j = ++vars->i;
	while (line[vars->i] && line[vars->i] != '\'')
		vars->i++;
	if (!line[vars->i])
	{
		printf("there is no closing (').\n");
		return (return_malloc_fail (str));
	}
	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
		return (return_malloc_fail (str));
	str = ft_str_concat(str, cut);
	vars->j = vars->i + 1;
	return (str);
}

char	*handle_double_quote(char *str, char *line,
	t_shell *sh, t_token_vars *vars)
{
	char	*cut;

	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
	{
		if (str)
			free(str);
		return (NULL);
	}
	str = ft_str_concat(str, cut);
	if (!str)
		return (NULL);
	vars->i++;
	vars->j = vars->i;
	str = ft_split_qoutation(line, str, sh, vars);
	return (str);
}

void	skip_white_spaces(char *line, t_token_vars *vars)
{
	vars->i = 0;
	while (line[vars->i] && is_white_space(line[vars->i]))
		vars->i++;
}

char	*handle_dollar_no_qautation(char *str, char *line,
	t_shell *sh, t_token_vars *vars)
{
	char			*cut;
	t_expand_ctx	ctx;

	cut = ft_str_cut(line, vars->j, vars->i);
	vars->j = ++vars->i;
	if (!cut)
		return (return_malloc_fail(str));
	str = ft_str_concat(str, cut);
	if (!str)
		return (NULL);
	ctx.i = vars->i;
	ctx.j = vars->j;
	ctx.inside_dquotes = 0;
	cut = ft_expand(line, sh, &ctx);
	if (!cut)
		return (return_malloc_fail(str));
	vars->i = ctx.i;
	vars->j = ctx.j;
	str = ft_str_concat(str, cut);
	if (!str)
		return (NULL);
	vars->i--;
	return (str);
}
