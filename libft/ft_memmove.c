/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/03 19:10:29 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:32:04 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*tmp1;
	unsigned char		*tmp2;
	unsigned char		*tmp3;
	size_t				i;

	i = 0;
	tmp1 = (const unsigned char *) src;
	tmp2 = (unsigned char *) dest;
	tmp3 = malloc (n * sizeof (unsigned char));
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		tmp3[i] = tmp1[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		tmp2[i] = tmp3[i];
		i++;
	}
	free (tmp3);
	return (dest);
}
