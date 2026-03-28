/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahal <arahal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:27:11 by arahal            #+#    #+#             */
/*   Updated: 2026/01/31 20:44:44 by arahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MS_LLONG_POS "9223372036854775807"
#define MS_LLONG_NEG "9223372036854775808"

int	is_numeric_str(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	abs_overflow(const char *digits, int neg)
{
	const char	*lim;
	size_t		len;
	size_t		i;

	lim = MS_LLONG_POS;
	if (neg)
		lim = MS_LLONG_NEG;
	i = 0;
	while (digits[i] == '0')
		i++;
	digits = digits + i;
	len = ft_strlen(digits);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (ft_strncmp(digits, lim, 19) > 0)
		return (1);
	return (0);
}

const char	*parse_sign(const char *s, int *neg)
{
	int	i;

	i = 0;
	*neg = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			*neg = 1;
		i++;
	}
	return (s + i);
}

int	digits_mod256(const char *digits)
{
	int	mod;

	mod = 0;
	while (*digits)
	{
		mod = (mod * 10 + (*digits - '0')) % 256;
		digits++;
	}
	return (mod);
}

int	parse_exit_code(const char *s, int *out_code)
{
	int			neg;
	int			mod;
	const char	*digits;

	if (!out_code || !is_numeric_str(s))
		return (0);
	digits = parse_sign(s, &neg);
	if (abs_overflow(digits, neg))
		return (0);
	mod = digits_mod256(digits);
	if (neg && mod != 0)
		mod = 256 - mod;
	*out_code = mod;
	return (1);
}
