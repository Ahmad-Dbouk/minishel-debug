/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_ifs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 00:00:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/23 00:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

static const char	*get_ifs(t_shell *sh)
{
	char	*ifs;

	ifs = env_get(sh, "IFS");
	if (!ifs)
		return (" \t\n");
	return (ifs);
}

static int	is_ifs_char(char c, const char *ifs)
{
	int	i;

	i = 0;
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	free_fields(char **fields)
{
	int	i;

	if (!fields)
		return ;
	i = 0;
	while (fields[i])
	{
		free(fields[i]);
		i++;
	}
	free(fields);
}

static char	**fields_from_word(const char *word, const char *ifs)
{
	char	**out;
	int		count;
	int		i;
	int		start;

	count = 0;
	i = 0;
	while (word[i] && is_ifs_char(word[i], ifs))
		i++;
	while (word[i])
	{
		while (word[i] && !is_ifs_char(word[i], ifs))
			i++;
		count++;
		while (word[i] && is_ifs_char(word[i], ifs))
			i++;
	}
	out = malloc(sizeof(char *) * (count + 1));
	if (!out)
		return (NULL);
	out[count] = NULL;
	i = 0;
	count = 0;
	while (word[i] && is_ifs_char(word[i], ifs))
		i++;
	while (word[i])
	{
		start = i;
		while (word[i] && !is_ifs_char(word[i], ifs))
			i++;
		out[count] = ft_substr(word, start, i - start);
		if (!out[count])
			return (free_fields(out), NULL);
		count++;
		while (word[i] && is_ifs_char(word[i], ifs))
			i++;
	}
	return (out);
}

static char	**single_field_dup(char *word)
{
	char	**out;

	out = malloc(sizeof(char *) * 2);
	if (!out)
		return (NULL);
	out[0] = ft_strdup(word);
	if (!out[0])
		return (free(out), NULL);
	out[1] = NULL;
	return (out);
}

char	**split_word_ifs(char *word, t_shell *sh)
{
	const char	*ifs;

	if (!word)
		return (single_field_dup(""));
	ifs = get_ifs(sh);
	if (!ifs[0])
		return (single_field_dup(word));
	return (fields_from_word(word, ifs));
}
