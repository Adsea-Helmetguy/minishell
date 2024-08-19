/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 16:31:26 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipelines_fds(t_pipelines *pipelines)
{
	close(pipelines->fd_in);
	close(pipelines->fd_out);
}

void	init_run_meta(t_pipelines *p)
{
	p->i = 0;
	p->end = p->components;
	signal_non_interaction();
}

void	init_run_loop_meta(t_pipelines *p)
{
	p->start = p->end;
	p->end = get_pipeline_end(p->start);
	if (p->end[1] && p->end[1]->parser_type == PARSER_PIPE)
		p->end += 2;
	run_connect_pipes(p, p->i);
}

void	run_connect_pipes(t_pipelines *pipelines, int i)
{
	pipelines->fd_in = dup(STDIN_FILENO);
	pipelines->fd_out = dup(STDOUT_FILENO);
	if (i > 0)
	{
		close(pipelines->fd_in);
		pipelines->fd_in = dup(pipelines->pipes[i -1][0]);
	}
	if (i < pipelines->n_pipes)
	{
		close(pipelines->fd_out);
		pipelines->fd_out = dup(pipelines->pipes[i][1]);
	}
}

int	is_parent_function(char **cmds)
{
	return (ft_strcmp(cmds[0], "export") == 0 || ft_strcmp(cmds[0], "cd") == 0
		|| ft_strcmp(cmds[0], "unset") == 0);
}
