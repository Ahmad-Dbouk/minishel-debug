/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split1_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/28 16:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*insert_at_tail_hd(t_token *head, char *val, int expand_heredoc)
{
	t_token	*cur;

	head = insert_at_tail(head, val, TOK_WORD);
	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->hd_expand = expand_heredoc;
	return (head);
}

t_token	*insert_fields_at_tail(t_token *head, char **fields)
{
	int	i;

	i = 0;
	while (fields[i])
	{
		head = insert_at_tail(head, fields[i], TOK_WORD);
		if (!head)
		{
			while (fields[i])
				free(fields[i++]);
			free(fields);
			return (NULL);
		}
		i++;
	}
	free(fields);
	return (head);
}
