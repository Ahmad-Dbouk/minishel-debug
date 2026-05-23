/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:02:49 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/27 13:03:07 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_redir_token(t_toktype type)
{
	if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC)
		return (1);
	return (0);
}

t_redir_type	return_redir_type(t_toktype type)
{
	if (type == TOK_REDIR_IN)
		return (R_IN);
	if (type == TOK_REDIR_OUT)
		return (R_OUT);
	if (type == TOK_APPEND)
		return (R_APPEND);
	if (type == TOK_HEREDOC)
		return (R_HEREDOC);
	return (0);
}

t_redir	*redir_new(t_redir_type type, char *target, int expand_heredoc)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->target = ft_strdup(target);
	if (!new->target)
	{
		free(new);
		return (NULL);
	}
	new->heredoc_fd = -1;
	new->expand_heredoc = expand_heredoc;
	new->next = NULL;
	return (new);
}

t_redir	*insert_redir_at_tail(t_redir *redir, t_redir *new_redir)
{
	t_redir	*cur;

	if (!redir)
		return (new_redir);
	cur = redir;
	while (cur->next)
		cur = cur->next;
	cur->next = new_redir;
	return (redir);
}

void	free_cmd_args(char	**argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	argv = NULL;
}
