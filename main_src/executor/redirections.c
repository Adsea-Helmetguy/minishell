/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:48:17 by keyu              #+#    #+#             */
/*   Updated: 2024/07/18 14:35:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	perror_exit(char *msg, int exit_code, t_pipelines *p)
{
	perror(msg);
	free_pipelines(p);
	free_struc_mini(p->mini);
	exit(exit_code);
}

static void	free_close(t_pipelines *p)
{
	close_all_pipes(p->n_pipes, p->pipes);
	free_pipelines(p);
	free_struc_mini(p->mini);
	close(p->fd_in);
	close(p->fd_out);
}

static void	heredoc_child(char *delimeter, t_pipelines *p)
{
	char	*tmp;
	int		tmp_fd;

	unlink("/tmp/minishell-1");
	tmp_fd = open("/tmp/minishell-1", O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (tmp_fd == -1)
		perror_exit("Heredoc Tmp File", 1, p);
	while (1)
	{
		heredoc_child_signal();
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ft_putendl_fd("minishell: warning: delimited by end-of-file", 2);
			break ;
		}
		if (!ft_strcmp(delimeter, tmp))
			break ;
		ft_putendl_fd(tmp, tmp_fd);
		free(tmp);
	}
	close(tmp_fd);
	free_close(p);
	exit(0);
}

static int	heredoc(char *delimeter, int *fd_in, int *fd_out, t_pipelines *p)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		heredoc_child(delimeter, p);
	heredoc_parent_signal();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		g_exit_status = status;
		p->mini->signal_fork = 0;
		if (g_exit_status > 0 && p->mini->is_it_builtin == 0)
			p->mini->signal_fork = 1;
		if (status)
			return (status);
		return (pl_open_in_file("/tmp/minishell-1", O_RDONLY, fd_in, fd_out));
	}
	return (1);
}

// returns 0 if ok, 1 if issue
int	update_fds(t_component **components,
	int *fd_in, int *fd_out, t_pipelines *p)
{
	int	res;

	res = 0;
	while (*components && (*components)->parser_type != PARSER_PIPE)
	{
		if ((*components)->parser_type == PARSER_OUTPUT)
			res = pl_open_out_file((*components)->string,
					O_WRONLY | O_CREAT | O_TRUNC, fd_in, fd_out);
		else if ((*components)->parser_type == PARSER_APPEND)
			res = pl_open_out_file((*components)->string,
					O_WRONLY | O_CREAT | O_APPEND, fd_in, fd_out);
		else if ((*components)->parser_type == PARSER_INPUT)
			res = pl_open_in_file((*components)->string,
					O_RDONLY, fd_in, fd_out);
		else if ((*components)->parser_type == PARSER_HEREDOC)
			res = heredoc((*components)->string, fd_in, fd_out, p);
		if (res)
			return (res);
		components++;
	}
	return (0);
}
