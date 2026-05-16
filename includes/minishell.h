/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:56:12 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/31 20:09:16 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"

typedef struct s_loop_ctx
{
	char	*line;
	int		interactive;
	t_shell	sh;
	t_token	*head;
	t_cmd	*p;
}	t_loop_ctx;

int		ms_loop(char **envp, char **argv);
int		exec_external(t_shell *sh, t_cmd *cmd, char **envp, char *path);
int		exec_one_pipeline(t_shell *sh, t_cmd *cmd);
int		exec_pipeline(t_shell *sh, t_cmd *cmds, int interactive);
char	*resolve_cmd_path(t_shell *sh, char *name, int *out_status);
void	free_2d(char **str);
int		has_slash(char *str);
char	*cmd_with_slash(char *name, int *out_status);
char	*return_path(char **paths, char *name, int *out_status);
int		is_dir(const char *path);
char	*ms_read_stdin_line(size_t len, size_t cap, int got_any);
int		loop_commands(t_cmd *cmd);

#endif
