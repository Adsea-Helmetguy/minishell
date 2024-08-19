/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:40:58 by mlow              #+#    #+#             */
/*   Updated: 2024/06/25 00:44:31 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_or_not(char **cmds, t_pipelines *p, char **envp)
{
	p->mini->is_it_builtin = 1;
	ft_builtin(cmds, p->mini);
	if ((p->mini->is_it_builtin) == 0)
		ft_nonbuiltin(cmds, p, envp);
}
