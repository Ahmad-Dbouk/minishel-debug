/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:12:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/15 19:28:38 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/minishell.h"

int	exec_env(t_shell *sh, t_cmd *cmd)
{
	t_env	*cur;

	if (!sh)
		return (1);
	if (cmd && cmd->argv && cmd->argv[1])
	{
		perror("minishell: env: too many arguments\n");
		return (1);
	}
	cur = sh->env;
	while (cur)
	{
		if (cur->has_value)
		{
			printf("%s=", cur->key);
			if (cur->value)
				printf("%s", cur->value);
			printf("\n");
		}
		cur = cur->next;
	}
	return (0);
}
