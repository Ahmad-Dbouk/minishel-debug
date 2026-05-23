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

static void	putstr_out(const char *s)
{
	if (s)
		ft_putstr_fd((char *)s, STDOUT_FILENO);
}

static void	putendl_out(const char *s)
{
	putstr_out(s);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	exec_pwd(void *sh)
{
	char		*cwd;
	const char	*pwd_fallback;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		putendl_out(cwd);
		free(cwd);
		return (0);
	}
	pwd_fallback = env_get(sh, "PWD");
	if (pwd_fallback && *pwd_fallback)
	{
		putendl_out(pwd_fallback);
		return (0);
	}
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
