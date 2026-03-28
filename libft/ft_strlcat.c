/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlcat.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 11:24:36 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:33:00 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	sizedest;
	size_t	sizesrc;
	size_t	i;

	sizedest = ft_strlen(dst);
	sizesrc = ft_strlen(src);
	if (size <= sizedest)
		return (sizesrc + size);
	i = sizedest;
	while (i < size - 1 && src[i - sizedest])
	{
		dst[i] = src[i - sizedest];
		i++;
	}
	dst[i] = '\0';
	return (sizesrc + sizedest);
}
