/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:46:05 by arahal            #+#    #+#             */
/*   Updated: 2026/01/31 18:21:23 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

int	is_valid_export_arg(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha((unsigned char)arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum((unsigned char)arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exec_export(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	status;
	int	ret;

	if (!cmd->argv[1])
	{
		print_export_list(sh);
		return (0);
	}
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		ret = export_assign(sh, cmd->argv[i]);
		if (ret == 2)
			return (1);
		if (ret == 1)
			status = 1;
		i++;
	}
	return (status);
}
