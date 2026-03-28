/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:47:11 by adbouk            #+#    #+#             */
/*   Updated: 2026/01/28 21:48:32 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_handle_line(char *line)
{
	printf("You typed: %s\n", line);
}

int	ms_grow_buf(char **buf, size_t *cap, size_t len)
{
	char	*newbuf;
	size_t	newcap;
	size_t	i;

	newcap = (*cap) * 2;
	newbuf = (char *)malloc(newcap);
	if (!newbuf)
		return (0);
	i = 0;
	while (i < len)
	{
		newbuf[i] = (*buf)[i];
		i++;
	}
	free(*buf);
	*buf = newbuf;
	*cap = newcap;
	return (1);
}

int	ms_read_char(char *c)
{
	ssize_t	r;

	r = read(STDIN_FILENO, c, 1);
	if (r <= 0)
		return ((int)r);
	return (1);
}

char	*ms_cleanup(char *buf)
{
	free(buf);
	return (NULL);
}

char	*ms_read_stdin_line(size_t len, size_t cap, int got_any)
{
	char	c;
	char	*buf;
	int		r;

	buf = (char *)malloc(cap);
	if (!buf)
		return (NULL);
	while (1)
	{
		r = ms_read_char(&c);
		if (r == 0)
			break ;
		if (r < 0)
			return (ms_cleanup(buf));
		got_any = 1;
		if (c == '\n')
			break ;
		if (len + 1 >= cap && !ms_grow_buf(&buf, &cap, len))
			return (ms_cleanup(buf));
		buf[len++] = c;
	}
	if (!got_any)
		return (ms_cleanup(buf));
	buf[len] = '\0';
	return (buf);
}
