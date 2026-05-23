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

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

static char	*append_tail(char *str, char *line, t_token_vars *vars)
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
		if (line[vars.i] == '\'' || line[vars.i] == '"'
			|| line[vars.i] == '$')
		{
			str = handle_no_qaute(str, line, sh, &vars);
			if (!str)
				return (NULL);
		}
		else
			vars.i++;
	}
	return (append_tail(str, line, &vars));
}
