/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/17 18:57:12 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_pipeline(t_component **curr_components,
	t_pipelines *pipelines, int i_pipeline)
{
	char	**cmds;

	close_unused_pipes(pipelines, i_pipeline);
	dup2(pipelines->fd_in, STDIN_FILENO);
	close(pipelines->fd_in);
	dup2(pipelines->fd_out, STDOUT_FILENO);
	close(pipelines->fd_out);
	cmds = get_args(curr_components);
	builtin_or_not(cmds, pipelines, pipelines->envp);
	free_args(cmds);
	close_all_pipes(pipelines->n_pipes, pipelines->pipes);
	free_pipelines(pipelines);
	free_struc_mini(pipelines->mini);
	exit(pipelines->mini->dollar_question_value);
}

void	special_f(t_pipelines *p, char **cmds)
{
	p->sin = dup(STDIN_FILENO);
	p->sout = dup(STDOUT_FILENO);
	dup2(p->fd_in, STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	ft_others(cmds, p->n_pipes, p->mini);
	dup2(p->sin, STDIN_FILENO);
	dup2(p->sout, STDOUT_FILENO);
	close(p->sin);
	close(p->sout);
	free_args(cmds);
	close_pipelines_fds(p);
	p->i += 1;
}

void	pipex(t_pipelines *p)
{
	p->last_pid = fork();
	if (p->last_pid == 0)
		exec_pipeline(p->start, p, p->i);
	close_pipelines_fds(p);
	p->i += 1;
}
