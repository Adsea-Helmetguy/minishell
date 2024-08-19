/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:48:54 by mlow              #+#    #+#             */
/*   Updated: 2024/07/21 11:41:23 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_export_notvalid(char *msg, t_mini *m, char ***name)
{
	int	array;

	ft_putstr_fd("export_function: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("': not a valid identifier.", 2);
	m->dollar_question_value = 1;
	if (name == NULL || !(*name) || (*name) == NULL)
		return ;
	array = 0;
	while ((*name)[array] != NULL)
	{
		free((*name)[array]);
		(*name)[array] = NULL;
		array++;
	}
	free((*name));
}

void	write_cd_notvalid(char *msg, t_mini *mini)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(msg, 2);
	mini->dollar_question_value = 1;
}

void	write_exit_notvalid(char **str, char *msg, int fd, t_mini *mini)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (str != NULL && *str != NULL)
	{
		ft_putstr_fd(*str, 2);
		free_args(str);
	}
	ft_putendl_fd(msg, 2);
	mini->dollar_question_value = 2;
	if (fd != 1)
	{
		free_struc_mini(mini);
		exit(fd);
	}
	mini->dollar_question_value = 1;
}

void	write_main_notvalid(char *msg, int fd, int exit_value)
{
	if (g_exit_status != 0)
		exit_value = g_exit_status;
	ft_putendl_fd(msg, fd);
	exit(exit_value);
}
