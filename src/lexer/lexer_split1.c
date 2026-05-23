/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:21:54 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 19:26:02 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

char	*ft_str_empty(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_str_cut(char *str, int start, int end)
{
	int		size;
	int		i;
	int		j;
	char	*new_str;

	size = end - start + 1;
	if (size <= 1)
		return (ft_str_empty());
	new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = start;
	while (j != end)
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	return (new_str);
}

void	free_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free (head);
		head = tmp;
	}
}

t_toktype	get_toktype(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TOK_PIPE);
	if (ft_strcmp (str, "<") == 0)
		return (TOK_REDIR_IN);
	if (ft_strcmp (str, ">") == 0)
		return (TOK_REDIR_OUT);
	if (ft_strcmp(str, ">>") == 0)
		return (TOK_APPEND);
	if (ft_strcmp (str, "<<") == 0)
		return (TOK_HEREDOC);
	return (TOK_WORD);
}

t_token	*insert_at_tail(t_token *head, char *val, t_toktype type)
{
	t_token	*cur;
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		free(val);
		free_token(head);
		return (NULL);
	}
	new_node->value = val;
	new_node->type = type;
	new_node->hd_expand = 0;
	new_node->next = NULL;
	cur = head;
	if (!head)
		return (new_node);
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
	return (head);
}

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
