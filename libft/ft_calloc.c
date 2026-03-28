/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_calloc.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 20:39:37 by adbouk			#+#	#+#			 */
/*   Updated: 2025/06/14 17:25:02 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	bytes;

	bytes = size * nmemb;
	if (nmemb && (bytes / nmemb) != size)
		return (NULL);
	tab = malloc (bytes);
	if (!tab)
		return (NULL);
	ft_bzero(tab, bytes);
	return (tab);
}
