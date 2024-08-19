/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:42:17 by mlow              #+#    #+#             */
/*   Updated: 2024/03/25 18:42:31 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_putenv_fd(t_mini *mini, char *arg, int fd)
{
	int	index;

	index = 0;
	ft_putstr_fd("env: ‘", 2);
	while (arg[index])
	{
		write(fd, &arg[index], 1);
		index++;
	}
	ft_putendl_fd("’: No such file or directory", 2);
	mini->dollar_question_value = 127;
}

//handle env -i ./minishell
void	env_function(int length, char **args, t_mini *mini)
{
	t_env		*env_tmp;

	if (length > 1)
	{
		ft_putenv_fd(mini, args[1], 2);
		return ;
	}
	env_tmp = mini->envpmen;
	while (env_tmp != NULL)
	{
		if (env_tmp->env_equal == 1)
		{
			ft_putstr_fd(env_tmp->name, 1);
			ft_putstr_fd("=", 1);
			if (env_tmp->value)
				ft_putendl_fd(env_tmp->value, 1);
			else if (!(env_tmp->value))
				ft_putstr_fd("\n", 1);
		}
		env_tmp = env_tmp->next;
	}
	env_tmp = mini->envpmen;
	mini->dollar_question_value = 0;
}
