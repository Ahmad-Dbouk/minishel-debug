/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adbouk <adbouk@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/04 21:43:43 by adbouk			#+#	#+#			 */
/*   Updated: 2026/01/25 14:31:26 by adbouk		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static int	check_zero(long n)
{
	if (n == 0)
		return (1);
	return (0);
}

static char	*create_zero(void)
{
	char	*tab;

	tab = malloc (2 * sizeof(char));
	tab[0] = '0';
	tab[1] = '\0';
	return (tab);
}

static int	ft_count_size(long n)
{
	long	cpy;
	int		size;

	size = 1;
	cpy = n;
	if (cpy < 0)
	{
		size++;
		cpy = -cpy;
	}
	while (cpy != 0)
	{
		size++;
		cpy = cpy / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*tab;
	long	nb;

	nb = n;
	if (check_zero(nb))
		return (create_zero());
	size = ft_count_size(nb);
	tab = malloc (size * sizeof (char));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	tab[--size] = '\0';
	while (nb != 0)
	{
		tab[--size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (tab);
}
