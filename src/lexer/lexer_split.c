/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:54:32 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 21:04:58 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include "../../includes/env.h"

void	skip_spaces(char *line, t_token_vars *vars)
{
	while (line[vars->i] && is_white_space(line[vars->i]))
		vars->i++;
}

static t_token	*consume_special_segment(char *line, t_shell *sh,
		t_token *head, t_token_vars *vars)
{
	char	*str;

	str = NULL;
	set_str_i_j(&str, vars);
	vars->split_fields = 1;
	while (is_special(line, *vars))
	{
		if (check(line, vars))
		{
			str = handle_no_qaute(str, line, sh, vars);
			if (!str)
				return (free_token(head), NULL);
		}
		vars->i++;
	}
	head = insert_no_qaute(str, line, head, sh, vars);
	if (!head)
		return (NULL);
	return (head);
}

t_token	*ft_split_line(char *line, t_shell *sh, t_token *head)
{
	char			*str;
	t_token_vars	vars;

	str = NULL;
	vars.i = 0;
	vars.j = 0;
	vars.split_fields = 0;
	vars.next = NULL;
	skip_white_spaces (line, &vars);
	while (line[vars.i])
	{
		if (line[vars.i] == '|' || line[vars.i] == '>' || line[vars.i] == '<')
		{
			head = handle_special_char (str, line, head, &vars);
			if (!head)
				return (NULL);
		}
		if (is_special(line, vars))
		{
			head = consume_special_segment(line, sh, head, &vars);
			if (!head)
				return (NULL);
		}
		skip_spaces(line, &vars);
	}
	return (head);
}

// int main(void)
// {
//	 t_shell *sh = NULL;
//	 char *tests[] = {
//		 "echo $ ah\"$name\"mad",
//		 "echo \"a | b\" | wc",
//		 "cat < in > out >> log",
//		 "cat << EOF | wc",
//		 "echo 'unterminated'",
//		 NULL};
//	 t_token *head = NULL;
//	 int i = 0;
//	 while (tests[i])
//	 {
//		 head = init_token(tests[i], sh);
//		 free_token(head);
//		 head = NULL;
//		 i++;
//	 }
//	 return (0);
// }

// if (line [i] && line[i] == '\'')
//		 {
//			 j = ++i;
//			 while (line[i] && line[i] != '\'')
//				 i++;
//			 if (!line[i])
//			 {
//				 printf("error, there is no closing (')\n");
//				 free_token(head);
//				 return (NULL);
//			 }
//			 str = ft_str_cut(line, j, i);
//			 if (str)
//				 head = insert_at_tail(head, str, TOK_WORD);
//			 i++;
//		 }
//		 if (line[i] && line[i] == '\"')
//		 {
//			 j = ++i;
//			 while (line[i] && line[i] != '\"')
//				 i++;
//			 if (!line[i])
//			 {
//				 printf("error, there is no closing (\")\n");
//				 free_token(head);
//				 return (NULL);
//			 }
//			 str = ft_str_cut(line, j, i);
//			 if (str)
//				 head = insert_at_tail(head, str, TOK_WORD);
//			 i++;
//		 }
