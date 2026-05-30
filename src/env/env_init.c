/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:24:21 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:24:22 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "../../includes/env.h"

static int	env_setup_shlvl(t_shell *sh)
{
	char	*cur;
	int		lvl;
	char	*lvl_str;

	cur = env_get(sh, "SHLVL");
	if (!cur)
		return (env_set(sh, "SHLVL", "1", 1));
	lvl = ft_atoi(cur);
	if (lvl < 0)
		lvl = 0;
	lvl_str = ft_itoa(lvl + 1);
	if (!lvl_str)
		return (-1);
	if (env_set(sh, "SHLVL", lvl_str, 1) < 0)
		return (free(lvl_str), -1);
	free(lvl_str);
	return (0);
}

static int	env_setup_pwd(t_shell *sh)
{
	char	cwd[PATH_MAX];

	if (env_get(sh, "PWD"))
		return (0);
	if (!getcwd(cwd, sizeof(cwd)))
		return (-1);
	return (env_set(sh, "PWD", cwd, 1));
}

static int	env_setup_underscore(t_shell *sh, char *argv0, int empty_envp)
{
	if (env_get(sh, "_"))
		return (0);
	if (empty_envp)
		return (env_set(sh, "_", "/usr/bin/env", 1));
	if (!argv0)
		argv0 = "";
	return (env_set(sh, "_", argv0, 1));
}

int	env_init_defaults(t_shell *sh, char *argv0, int empty_envp)
{
	if (!sh)
		return (-1);
	if (env_setup_shlvl(sh) < 0)
		return (-1);
	if (env_setup_pwd(sh) < 0)
		return (-1);
	if (env_setup_underscore(sh, argv0, empty_envp) < 0)
		return (-1);
	return (0);
}
