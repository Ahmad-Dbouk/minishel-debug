/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnstr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 13:15:56 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:30:39 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str1;
	char	*str2;

	if (!*little)
		return ((char *)big);
	str1 = (char *) big;
	str2 = (char *) little;
	i = 0;
	while (i < len && str1[i])
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (i + j < len && str1[i + j]
				&& str2[j] && str1[i + j] == str2[j])
				j++;
			if (!str2[j])
				return (str1 + i);
		}
		i++;
	}
	return (NULL);
}
