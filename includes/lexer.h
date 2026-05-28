/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:18:09 by adbouk            #+#    #+#             */
/*   Updated: 2026/03/28 16:21:43 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stddef.h>
# include <stdlib.h>
# include "./env.h"

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	int				hd_expand;
	struct s_token	*next;
}	t_token;

typedef struct s_token_vars
{
	int				i;
	int				j;
	int				split_fields;
	struct s_token	*next;
}	t_token_vars;

typedef struct s_expand_ctx
{
	int	i;
	int	j;
	int	inside_dquotes;
}	t_expand_ctx;

typedef struct s_insert_ctx
{
	t_shell			*sh;
	t_token_vars	*vars;
	int				ok;
}	t_insert_ctx;

t_token		*init_token(char *line, t_shell *sh);
int			check(char *line, t_token_vars *vars);
int			is_word_char(char *line, t_token_vars vars);
t_token		*handle_special_char(char *str, char *line,
				t_token *head, t_token_vars *vars);
void		set_str_i_j(char **str, t_token_vars *vars);
void		print_tokens(t_token *head);
void		free_token(t_token *head);
t_token		*insert_at_tail(t_token *head, char *val, t_toktype type);
t_token		*insert_fields_at_tail(t_token *head, char **fields);
char		**split_word_ifs(char *word, t_shell *sh);
int			is_ifs_char(char c, const char *ifs);
void		free_fields(char **fields);
char		**single_field_dup(char *word);
t_token		*insert_at_tail_hd(t_token *head, char *val, int expand_heredoc);
char		*expand_heredoc_line(t_shell *sh, char *line);
t_toktype	get_toktype(char *str);
void		free_token(t_token *head);
char		*ft_str_cut(char *str, int start, int end);
char		*ft_str_empty(void);
char		*ft_str_concat(char *s1, char *s2);
int			is_white_space(char c);
char		*handle_single_case(t_shell *sh, char *line, t_expand_ctx *ctx);
char		*ft_expand(char *line, t_shell *sh, t_expand_ctx *ctx);
char		*ft_end_split(char *line, char *str, char *cut, t_token_vars *vars);
t_token		*init_token(char *line, t_shell *sh);
void		print_tokens(t_token *head);
const char	*toktype_to_str(t_toktype type);
char		*ft_split_qoutation(char *line, char *str,
				t_shell *sh, t_token_vars *vars);

t_token		*ft_split_line(char *line, t_shell *sh, t_token *head);
t_token		*ft_verify_tokens(t_token *head);
t_token		*handle_pipe(char *str, char *line,
				t_token *head, t_token_vars *vars);
t_token		*handle_heredoc(char *str, char *line,
				t_token *head, t_token_vars *vars);
t_token		*handle_input_redirection(char *str, char *line,
				t_token *head, t_token_vars *vars);
t_token		*handle_append(char *str, char *line,
				t_token *head, t_token_vars *vars);
t_token		*handle_output_redirection(char *str, char *line,
				t_token *head, t_token_vars *vars);
char		*handle_dollar_no_qautation(char *str, char *line,
				t_shell *sh, t_token_vars *vars);
void		skip_white_spaces(char *line, t_token_vars *vars);
char		*handle_double_quote(char *str, char *line,
				t_shell *sh, t_token_vars *vars);
char		*handle_single_quote(char *str, char *line, t_token_vars *vars);
char		*return_malloc_fail(char *str);
char		*handle_no_qaute(char *str, char *line,
				t_shell *sh, t_token_vars *vars);
t_token		*insert_no_qaute(char *str, char *line,
				t_token **head, t_insert_ctx *ctx);
void		skip_spaces(char *line, t_token_vars *vars);
char		*extract_eof(char *line, t_token_vars *vars, int *expand_heredoc);
int			find_closing_quate(char *line, t_token_vars *vars, char c);
char		*handle_here_quate(char *str, char *line, t_token_vars *vars);
t_token		*ft_check_first(t_token *head);

#endif