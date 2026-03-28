/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 21:15:18 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:32:54 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	int		i;
	char	*tab;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	tab = malloc ((size1 + size2 + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		tab[size1 + i] = s2[i];
		i++;
	}
	tab[size1 + i] = '\0';
	return (tab);
}
