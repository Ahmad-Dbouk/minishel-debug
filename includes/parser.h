/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:02:01 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/15 19:24:23 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "lexer.h"

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
	int				expand_heredoc;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_word
{
	char			*str;
	struct s_word	*next;
}	t_word;

typedef struct s_parse_ctx
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*new_cmd;
	t_word	*words;
}	t_parse_ctx;

// t_cmd			*parse_token(t_token *token, t_token *cur);
t_cmd			*parse_token(t_token *token);
void			print_cmd_list(t_cmd *head);
void			free_cmds(t_cmd *cmd);
int				is_redir_token(t_toktype type);
t_redir_type	return_redir_type(t_toktype type);
t_redir			*redir_new(t_redir_type type, char *target, int expand_heredoc);
t_redir			*insert_redir_at_tail(t_redir *redir, t_redir *new_redir);
void			free_cmd_args(char	**argv);
int				init_new_cmd(t_cmd **new_cmd);
t_cmd			*insert_cmd_at_tail(t_cmd *cmd, t_cmd *new_cmd);
char			**convert_to_argv(t_word *words);
void			free_argv(char **argv, int count);
void			free_cmds(t_cmd *cmd);
void			free_redirs(t_redir *r);
t_word			*insert_word_at_tail(t_word *word, t_word *new_word);
t_word			*word_new(char *value);
void			free_words(t_word *word);
int				init_cmd(t_cmd **new_cmd, t_cmd **cmd);
void			free_argv2(char **argv);
void			free_cmd_one(t_cmd *cmd);
void			free_cmds2(t_cmd *cmd);
void			free_parser(t_token *token, t_cmd *cmd, t_word *words);
char			**alloc_null_args(void);
int				handle_redir_token(t_parse_ctx *ctx, t_token **cur);
int				handle_pipe_token(t_parse_ctx *ctx);
int				insert_cmd_on_pipe(t_cmd *new_cmd, t_word **words,
					t_token *token, t_cmd *cmd);
int				set_cmd_argv(t_word **words, t_cmd *new_cmd,
					t_token *token, t_cmd *cmd);
int				set_cmd_argv_on_pipe(t_word **words, t_cmd *new_cmd,
					t_token *token, t_cmd *cmd);

#endif
