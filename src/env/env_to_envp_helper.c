/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:25:18 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:25:25 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int	count_printable(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->has_value)
			count++;
		env = env->next;
	}
	return (count);
}
