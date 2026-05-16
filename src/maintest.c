/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   maintest.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/01/25 14:44:02 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:44:44 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"
#include "../includes/lexer.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	return (ms_loop(envp, argv));
}
