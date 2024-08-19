/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 16:31:26 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pl_open_out_file(char *filename, int flags, int *fd_in, int *fd_out)
{
	int	tmp;

	close(*fd_out);
	tmp = open(filename, flags, 0644);
	if (tmp == -1)
	{
		perror(filename);
		close(*fd_in);
		return (1);
	}
	*fd_out = tmp;
	return (0);
}

int	pl_open_in_file(char *filename, int flags, int *fd_in, int *fd_out)
{
	int	tmp;

	close(*fd_in);
	tmp = open(filename, flags);
	if (tmp == -1)
	{
		perror(filename);
		close(*fd_out);
		return (1);
	}
	*fd_in = tmp;
	return (0);
}

void	close_unused_pipes(t_pipelines *pipelines, int i_pipeline)
{
	int	j;

	j = 0;
	while (j < pipelines->n_pipes)
	{
		if (j != i_pipeline - 1)
			close(pipelines->pipes[j][0]);
		if (j != i_pipeline)
			close(pipelines->pipes[j][1]);
		j++;
	}
}

void	close_all_pipes(int n_pipes, int **pipes)
{
	int	j;

	j = 0;
	while (j < n_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
