/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:10:00 by arahal            #+#    #+#             */
/*   Updated: 2026/01/25 17:58:06 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_unset_key(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!ft_isalpha((unsigned char)s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_error(const char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	exec_unset(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
		return (0);
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_unset_key(cmd->argv[i]))
		{
			unset_error(cmd->argv[i]);
			status = 1;
		}
		else
			env_unset(sh, cmd->argv[i]);
		i++;
	}
	return (status);
}
