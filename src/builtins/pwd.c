/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:10:58 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:11:27 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../../includes/minishell.h"

static void	putstr_fd(const char *s)
{
	if (!s)
		return ;
	printf("%s", s);
}

static void	putendl_fd(const char *s)
{
	putstr_fd(s);
	printf("\n");
}

int	exec_pwd(void *sh)
{
	char		*cwd;
	const char	*pwd_fallback;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		putendl_fd(cwd);
		free(cwd);
		return (0);
	}
	pwd_fallback = env_get(sh, "PWD");
	if (pwd_fallback && *pwd_fallback)
	{
		putendl_fd(pwd_fallback);
		return (0);
	}
	putstr_fd("minishell: pwd: ");
	putendl_fd(strerror(errno));
	return (1);
}
