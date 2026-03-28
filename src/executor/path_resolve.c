/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:21:24 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 17:53:24 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cmd_without_slash(t_shell *sh, char *name, int *out_status)
{
	char	**paths;
	char	*path;
	char	*tmp;

	tmp = env_get(sh, "PATH");
	if (!tmp || tmp[0] == '\0')
	{
		*out_status = 127;
		return (NULL);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	path = return_path(paths, name, out_status);
	free_2d(paths);
	return (path);
}

char	*resolve_cmd_path(t_shell *sh, char *name, int *out_status)
{
	if (!name || name[0] == '\0')
		return (*out_status = 127, NULL);
	*out_status = 0;
	if (has_slash(name))
		return (cmd_with_slash(name, out_status));
	return (cmd_without_slash(sh, name, out_status));
}
