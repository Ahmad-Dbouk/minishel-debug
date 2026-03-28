/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:12:08 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:12:09 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

void	env_clear(t_env **env)
{
	t_env	*next;

	if (!env)
		return ;
	while (*env)
	{
		next = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = next;
	}
}
