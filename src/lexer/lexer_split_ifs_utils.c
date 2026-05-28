/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_ifs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/28 16:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_ifs_char(char c, const char *ifs)
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

char	**single_field_dup(char *word)
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
