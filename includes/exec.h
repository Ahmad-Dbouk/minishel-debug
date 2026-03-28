/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:00:06 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/25 15:00:52 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "./env.h"
# include "./parser.h"

typedef struct s_stdio_bak
{
	int	in;
	int	out;
}	t_stdio_bak;

int		apply_redirs(t_shell *sh, t_cmd *cmd);
int		stdio_backup(t_stdio_bak *bak);
void	stdio_restore(t_stdio_bak *bak);
void	child_process(t_cmd *cmd, char **envp, char *path);

#endif
