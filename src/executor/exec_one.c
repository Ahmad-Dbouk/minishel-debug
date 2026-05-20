/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:22:59 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:23:01 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_one_pipeline(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**envp;

	if (!sh || !cmd)
		return (1);
	if (cmd->next)
		return (sh->last_status = 1, 1);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (sh->last_status = 0, 0);
	path = resolve_cmd_path(sh, cmd->argv[0], &sh->last_status);
	if (!path)
	{
		if (sh->last_status == 127)
			print_cmd_not_found(cmd->argv[0]);
		return (sh->last_status);
	}
	envp = env_to_envp(sh);
	if (!envp)
		return (free(path), sh->last_status = 1, 1);
	return (exec_external(sh, cmd, envp, path));
}
