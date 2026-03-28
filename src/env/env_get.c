/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:23:54 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:24:17 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int	key_match(const char *a, const char *b)
{
	size_t	la;
	size_t	lb;

	if (!a || !b)
		return (0);
	la = ft_strlen(a);
	lb = ft_strlen(b);
	if (la != lb)
		return (0);
	return (ft_strncmp(a, b, la) == 0);
}

t_env	*env_find(t_env *env, const char *key)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (key_match(key, cur->key))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

char	*env_find_alias(t_env *env, const char *key)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (key_match(key, cur->key))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

char	*env_get(t_shell *sh, const char *key)
{
	t_env	*tmp;

	if (!sh || !key)
		return ((tmp = NULL), NULL);
	tmp = env_find(sh->env, key);
	if (!tmp || !tmp->has_value)
		return (NULL);
	return (tmp->value);
}

int	env_has(t_shell *sh, const char *key)
{
	if (!sh || !key)
		return (0);
	return (env_find(sh->env, key) != NULL);
}
