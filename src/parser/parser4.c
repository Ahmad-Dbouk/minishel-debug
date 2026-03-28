/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:09:30 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 19:51:40 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	init_cmd(t_cmd **new_cmd, t_cmd **cmd)
{
	*new_cmd = malloc (sizeof(t_cmd));
	if (!*new_cmd)
		return (1);
	(*new_cmd)->argv = NULL;
	(*new_cmd)->next = NULL;
	(*new_cmd)->redirs = NULL;
	(*cmd) = NULL;
	return (0);
}

t_word	*word_new(char *value)
{
	t_word	*new;

	new = malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->str = ft_strdup(value);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_word	*insert_word_at_tail(t_word *word, t_word *new_word)
{
	t_word	*cur;

	if (!word)
		return (new_word);
	cur = word;
	while (cur->next)
		cur = cur->next;
	cur->next = new_word;
	return (word);
}

void	free_words(t_word *word)
{
	t_word	*cur;

	while (word)
	{
		cur = word;
		word = word->next;
		free(cur->str);
		free(cur);
	}
}

void	free_redirs(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		free(r->target);
		free(r);
		r = next;
	}
}
