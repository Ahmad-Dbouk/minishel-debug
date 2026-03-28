/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:34:21 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/27 13:14:49 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
	{
		printf("	argv: (null)\n");
		return ;
	}
	printf("	argv:\n");
	while (argv[i])
	{
		printf("	  [%d] \"%s\"\n", i, argv[i]);
		i++;
	}
	if (i == 0)
		printf("	  (empty)\n");
}

static void	print_redirs(t_redir *r)
{
	int			i;
	const char	*target;

	i = 0;
	if (!r)
	{
		printf("	redirs: (none)\n");
		return ;
	}
	printf("	redirs:\n");
	while (r)
	{
		if (r->target)
			target = r->target;
		else
			target = "(null)";
		printf("	  (%d) type=%d, target=%s, heredoc_fd=%d\n",
			i, (int)r->type, target, r->heredoc_fd);
		r = r->next;
		i++;
	}
}

void	print_cmd_list(t_cmd *head)
{
	int	idx;

	idx = 0;
	if (!head)
	{
		printf("cmd list: (null)\n");
		return ;
	}
	while (head)
	{
		printf("CMD #%d:\n", idx);
		print_argv(head->argv);
		print_redirs(head->redirs);
		head = head->next;
		idx++;
		printf("\n");
	}
}
