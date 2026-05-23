/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:04:29 by adbouk            #+#    #+#             */
/*   Updated: 2026/02/21 15:55:51 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_errno(const char *ctx, const char *target)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)ctx, 2);
	if (target && target[0])
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)target, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static int	cd_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}

static int	cd_home_not_set(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (1);
}

int	exec_cd(t_shell *sh, t_cmd *cmd, char *target, char *oldpwd)
{
	char	newpwd[PATH_MAX];

	if (!cmd || !cmd->argv)
		return (1);
	if (cmd->argv[1] && cmd->argv[2])
		return (cd_too_many_args());
	if (!cmd->argv[1])
	{
		target = env_get(sh, "HOME");
		if (!target || target[0] == '\0')
			return (cd_home_not_set());
	}
	else
		target = cmd->argv[1];
	oldpwd = env_get(sh, "PWD");
	if (chdir(target) == -1)
	{
		return (print_errno("cd", target));
	}
	if (oldpwd)
		env_set(sh, "OLDPWD", oldpwd, 1);
	if (getcwd(newpwd, sizeof(newpwd)) != NULL)
		env_set(sh, "PWD", newpwd, 1);
	return (0);
}
