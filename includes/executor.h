/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:46:39 by mlow              #+#    #+#             */
/*   Updated: 2024/07/08 15:26:17 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

typedef struct s_mini	t_mini;

typedef struct s_pipelines
{
	int			n_pipes;
	int			**pipes;
	t_component	**components;
	t_mini		*mini;
	char		**envp;
	int			fd_in;
	int			fd_out;
	t_component	**start;
	t_component	**end;
	pid_t		last_pid;
	int			i;
	int			sin;
	int			sout;
}	t_pipelines;

// executor.c
int			execute_tokens(t_token **tokens, t_mini *mini, char **envp);
// executor_utils.c
void		close_pipelines_fds(t_pipelines *pipelines);
void		init_run_meta(t_pipelines *p);
void		init_run_loop_meta(t_pipelines *p);
void		run_connect_pipes(t_pipelines *pipelines, int i);
int			is_parent_function(char **cmds);
// executor_utils2.c
void		special_f(t_pipelines *p, char **cmds);
void		pipex(t_pipelines *p);
// component_utils.c
void		free_args(char **args);
char		**get_args(t_component **components);
void		pargs(char **args);
// piping.c
t_component	**get_pipeline_end(t_component **components);
int			count_pipes(t_component **components);
int			**setup_pipes(int pipes);
void		free_pipes(int **pipes, int n_pipe);
void		free_pipelines(t_pipelines *pipelines);
// piping_2.c
int			pl_open_out_file(char *filename, int flags,
				int *fd_in, int *fd_out);
int			pl_open_in_file(char *filename, int flags, int *fd_in, int *fd_out);
void		close_unused_pipes(t_pipelines *pipelines, int i_pipeline);
void		close_all_pipes(int n_pipes, int **pipes);
// redirections.c
int			update_fds(t_component **components, int *fd_in,
				int *fd_out, t_pipelines *p);

#endif
