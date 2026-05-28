/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:42:23 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 19:30:01 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

char	*ft_str_concat(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		j;
	size_t	size;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	size = (ft_strlen(s1) + ft_strlen(s2));
	tab = malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (free(s1), free(s2), tab);
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static char	*expand_braced_var(t_shell *sh, char *line, t_expand_ctx *ctx)
{
	char	*str;
	char	*tmp;

	ctx->j = ++(ctx->i);
	while (line[ctx->i] && line[ctx->i] != '}')
		(ctx->i)++;
	if (!line[ctx->i])
		return (NULL);
	str = ft_str_cut(line, ctx->j, ctx->i);
	if (!str)
		return (NULL);
	tmp = env_find_alias(sh->env, str);
	free(str);
	(ctx->j) = ++(ctx->i);
	if (!tmp)
		return (ft_str_empty());
	return (ft_strdup(tmp));
}

char	*handle_single_case(t_shell *sh, char *line, t_expand_ctx *ctx)
{
	if (line[ctx->i] && line[ctx->i] == '?')
		return ((ctx->j) = ++(ctx->i), ft_itoa(sh->last_status));
	if (line[ctx->i] == '{')
		return (expand_braced_var(sh, line, ctx));
	if (!line[ctx->i])
		return (ft_strdup("$"));
	if (line[ctx->i] == '"' || line[ctx->i] == '\'')
	{
		if (ctx->inside_dquotes)
			return (ft_strdup("$"));
		return (ft_str_empty());
	}
	return (ft_strdup("$"));
}

char	*ft_expand(char *line, t_shell *sh, t_expand_ctx *ctx)
{
	char	*tmp;
	char	*str;

	tmp = NULL;
	while (line[ctx->i] && (ft_isalnum(line[ctx->i]) || line[ctx->i] == '_'))
		(ctx->i)++;
	if ((ctx->i) == (ctx->j))
		return (handle_single_case(sh, line, ctx));
	str = ft_str_cut(line, ctx->j, ctx->i);
	if (!str)
		return (NULL);
	tmp = env_find_alias(sh->env, str);
	free(str);
	ctx->j = ctx->i;
	if (!tmp)
		return (ft_str_empty());
	return (ft_strdup(tmp));
}
