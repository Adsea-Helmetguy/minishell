/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:06 by mlow              #+#    #+#             */
/*   Updated: 2024/03/12 15:37:13 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_echo(int l, int array, char *string, int fd)
{
	ft_putstr_fd(string, fd);
	if ((array + 1) < l)
		write(1, " ", 1);
}

void	echo_function(int length, char **args, t_mini *mini)
{
	int		array;

	array = 1;
	if (!(args[1]))
	{
		write(1, "\n", 1);
		mini->dollar_question_value = 0;
		return ;
	}
	if (ft_strcmp(args[1], "-n") == 0)
		array++;
	while (array < length)
	{
		if (args[array])
			write_echo(length, array, args[array], 1);
		array++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		write(1, "\n", 1);
	mini->dollar_question_value = 0;
}
