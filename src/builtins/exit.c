/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:00:07 by arahal            #+#    #+#             */
/*   Updated: 2026/01/31 20:45:30 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

#define MS_LLONG_POS "9223372036854775807"
#define MS_LLONG_NEG "9223372036854775808"

void	exit_error(int type, const char *arg)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (type == 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

void	exit_no_args(t_shell *sh, int interactive)
{
	if (interactive)
		ft_putstr_fd("exit\n", 1);
	exit(sh->last_status);
}

void	exit_invalid(const char *arg, int interactive)
{
	if (interactive)
		ft_putstr_fd("exit\n", 1);
	exit_error(1, arg);
	exit(2);
}

int	exec_exit(t_shell *sh, t_cmd *cmds, int interactive)
{
	int	code;

	code = 0;
	if (!cmds || !cmds->argv)
		return (1);
	if (!cmds->argv[1])
		exit_no_args(sh, interactive);
	if (!parse_exit_code(cmds->argv[1], &code))
		exit_invalid(cmds->argv[1], interactive);
	if (cmds->argv[2])
	{
		exit_error(2, NULL);
		return (1);
	}
	if (interactive)
		ft_putstr_fd("exit\n", 1);
	exit(code);
}
