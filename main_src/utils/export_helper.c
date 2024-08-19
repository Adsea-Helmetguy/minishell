/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:48:01 by mlow              #+#    #+#             */
/*   Updated: 2024/05/16 12:48:38 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ftps_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_env	*ft_sort_list(t_env *e)
{
	t_env	*env_tmp;

	env_tmp = e;
	while (env_tmp->next != NULL)
	{
		if (ft_strcmp(env_tmp->name, env_tmp->next->name) > 0)
		{
			ftps_swap(&(env_tmp->name), &(env_tmp->next->name));
			ftps_swap(&(env_tmp->value), &(env_tmp->next->value));
			int_swap(&(env_tmp->env_equal), &(env_tmp->next->env_equal));
			env_tmp = e;
		}
		else
			env_tmp = env_tmp->next;
	}
	env_tmp = e;
	return (env_tmp);
}
