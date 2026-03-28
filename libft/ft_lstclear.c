/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/06 14:30:05 by adbouk			#+#	#+#			 */
/*   Updated: 2025/06/12 17:44:09 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*tmp;

	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		ft_lstdelone(cur, del);
		cur = tmp;
	}
	*lst = NULL;
}
