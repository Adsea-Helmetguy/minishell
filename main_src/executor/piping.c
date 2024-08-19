/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 16:31:26 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_component	**get_pipeline_end(t_component **components)
{
	t_component	**end;

	end = components;
	while (*end && (*end)->parser_type != PARSER_PIPE)
		end++;
	return (end - 1);
}

int	count_pipes(t_component **components)
{
	int	count;

	count = 0;
	while (*components)
	{
		if ((*components)->parser_type == PARSER_PIPE)
			count++;
		components++;
	}
	return (count);
}

int	**setup_pipes(int pipes)
{
	int	**fds;
	int	i;

	i = 0;
	fds = malloc(sizeof(int *) * pipes);
	while (i < pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

void	free_pipes(int **pipes, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe)
		free(pipes[i++]);
	free(pipes);
}

void	free_pipelines(t_pipelines *pipelines)
{
	free_components(pipelines->components);
	free_pipes(pipelines->pipes, pipelines->n_pipes);
}
