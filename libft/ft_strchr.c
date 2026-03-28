/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 12:26:12 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:32:44 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;
	char	*str;

	size = ft_strlen (s);
	i = 0;
	str = (char *)s;
	if (!s)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
