/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strrchr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 12:39:21 by adbouk			#+#	#+#			 */
/*   Updated: 2025/06/09 14:50:38 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = ft_strlen(s);
	str = (char *)s;
	if (!s)
		return (NULL);
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			return (str + i);
		}
		i--;
	}
	return (NULL);
}
