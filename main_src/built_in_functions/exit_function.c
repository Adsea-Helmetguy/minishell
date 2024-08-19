/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:50:12 by mlow              #+#    #+#             */
/*   Updated: 2024/07/21 13:40:41 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exit_minus(char **args, int index, t_mini *m, int l)
{
	if (args[1][0] == '-' || args[1][0] == '+')
	{
		index++;
		if (args[1][1] == '-' && !args[1][2])
		{
			free_struc_mini(m);
			free_args(args);
			if (g_exit_status > 0 && l == 2)
				exit(g_exit_status);
			exit(m->dollar_question_value);
		}
	}
	return (index);
}

static void	exit_helper(int length, char **args, t_mini *mini)
{
	int	index;

	if (length == 2 && args[1])
	{
		index = -1;
		index = exit_minus(args, index, mini, length);
		while (args[1][++index])
		{
			if (ft_isdigit(args[1][index]) == 0)
			{
				write_exit_notvalid(args,
					"numeric argument required", 2, mini);
			}
		}
		mini->dollar_string = ft_strdup(args[1]);
		mini->dollar_question_value = ft_atoi(args[1]);
		free_env(mini);
		return ;
	}
}

int	exit_function(char **args, t_mini *mini)
{
	int	length;

	mini->is_it_builtin = 1;
	length = 0;
	while (args[length])
		length++;
	ft_putendl_fd("exit", 1);
	if (length > 2)
	{
		free_args(args);
		write_exit_notvalid(NULL, "too many arguments", 1, mini);
		return (1);
	}
	exit_helper(length, args, mini);
	free_struc_mini(mini);
	free_args(args);
	if (g_exit_status > 0 && length == 1)
		exit(g_exit_status);
	exit(mini->dollar_question_value);
}
