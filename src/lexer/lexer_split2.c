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

char	*handle_single_case(t_shell *sh, char *line, int *i, int *j)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	if (line[*i] && line[*i] == '?')
		return ((*j) = ++(*i), ft_itoa(sh->last_status));
	if (line[*i] == '{')
	{
		*j = ++(*i);
		while (line[*i] && line[*i] != '}')
			(*i)++;
		if (!line[*i])
			return (NULL);
		str = ft_str_cut(line, *j, *i);
		if (!str)
			return (NULL);
		tmp = env_find_alias(sh->env, str);
		free(str);
		(*j) = ++(*i);
		if (!tmp)
			return (ft_str_empty());
		return (ft_strdup(tmp));
	}
	return (ft_strdup ("$"));
}

char	*ft_expand(char *line, int *i, int *j, t_shell *sh)
{
	char	*tmp;
	char	*str;

	(void)sh;
	tmp = NULL;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if ((*i) == (*j))
		return (handle_single_case(sh, line, i, j));
	str = ft_str_cut(line, *j, *i);
	if (!str)
		return (NULL);
	tmp = env_find_alias(sh->env, str);
	free(str);
	(*j) = (*i);
	if (!tmp)
		return (ft_str_empty());
	return (ft_strdup(tmp));
}

char	*ft_end_split(char *line, char *str, char *cut, t_token_vars *vars)
{
	if (!line[vars->i])
		return (free(str), NULL);
	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
		return (free(str), NULL);
	str = ft_str_concat(str, cut);
	vars->j = (vars->i) + 1;
	return (str);
}
