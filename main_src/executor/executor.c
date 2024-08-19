/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/18 14:33:13 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_parent(t_pipelines *pipelines, int last_pid)
{
	int		status;
	pid_t	wpid;

	close_all_pipes(pipelines->n_pipes, pipelines->pipes);
	signal_non_interaction_parent(pipelines);
	if (last_pid == -1)
		return ;
	status = 0;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (wpid == last_pid)
			{
				pipelines->mini->dollar_question_value
					= WEXITSTATUS(status);
			}
		}
		else
			pipelines->mini->signal_fork = 1;
		if (wpid <= 0)
			break ;
	}
}

static void	run_all_pipelines(t_pipelines *p)
{
	char	**cmds;

	init_run_meta(p);
	p->last_pid = -1;
	while (p->i < p->n_pipes + 1)
	{
		init_run_loop_meta(p);
		if (update_fds(p->start, &(p->fd_in), &(p->fd_out), p))
		{
			p->mini->dollar_question_value = 1;
			close_pipelines_fds(p);
			p->i += 1;
			continue ;
		}
		cmds = get_args(p->start);
		if (is_parent_function(cmds))
		{
			special_f(p, cmds);
			continue ;
		}
		free_args(cmds);
		pipex(p);
	}
	run_parent(p, p->last_pid);
}

static void	init_pipelines(t_pipelines *pipelines,
	t_component **components, char **envp, t_mini *mini)
{
	pipelines->components = components;
	pipelines->n_pipes = count_pipes(components);
	pipelines->pipes = setup_pipes(pipelines->n_pipes);
	pipelines->envp = envp;
	pipelines->mini = mini;
}

int	execute_tokens(t_token **tokens, t_mini *mini, char **envp)
{
	t_component	**components;
	t_pipelines	pipelines;
	char		**args;

	components = parse_tokens(tokens);
	free_tokens(tokens);
	if (components == 0)
	{
		ft_putendl_fd("Syntax error", 2);
		return (1);
	}
	init_pipelines(&pipelines, components, envp, mini);
	args = get_args(components);
	if (ft_strcmp(args[0], "exit") == 0 && pipelines.n_pipes == 0)
	{
		free_pipelines(&pipelines);
		mini->signal_fork = 0;
		if (exit_function(args, mini) == 1)
			return (0);
	}
	free_args(args);
	run_all_pipelines(&pipelines);
	free_pipelines(&pipelines);
	return (0);
}
