/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcpy.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/03 18:34:01 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:32:01 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*tab1;
	unsigned char		*tab2;	

	i = 0;
	tab1 = (const unsigned char *)src;
	tab2 = (unsigned char *)dest;
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		tab2[i] = tab1[i];
		i++;
	}
	return (dest);
}
