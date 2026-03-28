/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:25:35 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:25:39 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static void	env_del_one(t_env	*node)
{
	if (!node)
		return ;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

int	env_unset(t_shell	*sh, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!sh || !key)
		return (0);
	prev = NULL;
	cur = sh->env;
	while (cur)
	{
		if (key_match(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				sh->env = cur->next;
			env_del_one(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
