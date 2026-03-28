/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:57:34 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:28:37 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include "./parser.h"
# include "./env.h"

typedef enum e_builtin
{
	BI_NONE = 0,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_builtin;

int		exec_echo(t_cmd *cmds, int i, int is_n);
int		exec_cd(t_shell *sh, t_cmd *cmd, char *target, char *oldpwd);
int		exec_pwd(void *sh);
int		exec_env(t_shell *sh, t_cmd *cmd);
void	print_export_list(t_shell *sh);
int		exec_exit(t_shell *sh, t_cmd *cmds, int interactive);
int		parse_exit_code(const char *s, int *out_code);

#endif