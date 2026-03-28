/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:53:06 by arahal            #+#    #+#             */
/*   Updated: 2026/01/28 22:02:18 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

int	export_assign_helper(t_shell *sh, const char *arg,
		char *key, char *val)
{
	int		i;
	int		has_eq;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (!key)
		return (2);
	has_eq = 0;
	if (arg[i] == '=')
	{
		has_eq = 1;
		val = ft_strdup(arg + i + 1);
		if (!val)
			return (free(key), 2);
		env_set(sh, key, val, 1);
	}
	if (!has_eq && !env_get(sh, key))
		env_set(sh, key, NULL, 0);
	free(key);
	free(val);
	return (0);
}

int	export_assign(t_shell *sh, const char *arg)
{
	char	*key;
	char	*val;

	if (!is_valid_export_arg(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	key = NULL;
	val = NULL;
	return (export_assign_helper(sh, arg, key, val));
}
