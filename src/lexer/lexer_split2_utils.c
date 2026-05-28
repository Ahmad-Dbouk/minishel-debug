/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split2_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:00 by adbouk            #+#    #+#             */
/*   Updated: 2026/05/28 16:00:00 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*ft_end_split(char *line, char *str, char *cut, t_token_vars *vars)
{
	if (!line[vars->i])
		return (free(str), NULL);
	cut = ft_str_cut(line, vars->j, vars->i);
	if (!cut)
		return (free(str), NULL);
	str = ft_str_concat(str, cut);
	vars->j = (vars->i) + 1;
	return (str);
}
