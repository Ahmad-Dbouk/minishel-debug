/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_substr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 20:37:12 by adbouk			#+#	#+#			 */
/*   Updated: 2025/06/12 19:41:01 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			size_s;
	size_t			size;
	size_t			i;
	char			*tab;

	size_s = ft_strlen (s);
	if (size_s < start)
		return (ft_strdup (""));
	if (size_s - start > len)
		size = len;
	else
		size = size_s - start;
	tab = malloc ((size + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = s[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
