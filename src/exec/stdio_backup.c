/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_backup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:26:20 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:26:25 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

int	stdio_backup(t_stdio_bak *bak)
{
	bak->in = dup(STDIN_FILENO);
	if (bak->in < 0)
		return (1);
	bak->out = dup(STDOUT_FILENO);
	if (bak->out < 0)
	{
		close(bak->in);
		bak->in = -1;
		return (1);
	}
	return (0);
}

void	stdio_restore(t_stdio_bak *bak)
{
	if (bak->in >= 0)
	{
		dup2(bak->in, STDIN_FILENO);
		close(bak->in);
		bak->in = -1;
	}
	if (bak->out >= 0)
	{
		dup2(bak->out, STDOUT_FILENO);
		close(bak->out);
		bak->out = -1;
	}
}
