/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouk <adbouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:19:34 by arahal            #+#    #+#             */
/*   Updated: 2026/03/15 19:33:02 by adbouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export_one(t_env *e)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(e->key, STDOUT_FILENO);
	if (e->value != NULL)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(e->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static int	env_count_all(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static void	env_sort_by_key(t_env **arr, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_list(t_shell *sh)
{
	t_env	**arr;
	t_env	*cur;
	int		n;
	int		i;

	if (!sh || !sh->env)
		return ;
	n = env_count_all(sh->env);
	if (n <= 0)
		return ;
	arr = (t_env **)malloc(sizeof(t_env *) * n);
	if (!arr)
		return ;
	i = 0;
	cur = sh->env;
	while (cur)
	{
		arr[i++] = cur;
		cur = cur->next;
	}
	env_sort_by_key(arr, n);
	i = -1;
	while (i++, i < n)
		print_export_one(arr[i]);
	free(arr);
}
