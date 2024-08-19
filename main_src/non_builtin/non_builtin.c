/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:21:57 by mlow              #+#    #+#             */
/*   Updated: 2024/06/29 18:47:49 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path(char *name, t_env *env_tmp)
{
	char	*path_directories;
	char	*tmp_path;

	path_directories = (char *)malloc(sizeof(char) * 1);
	if (!path_directories)
		return (NULL);
	path_directories[0] = '\0';
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->name, name) == 0)
		{
			tmp_path = path_directories;
			path_directories = ft_strjoin(tmp_path, (env_tmp->value));
			free(tmp_path);
			return (path_directories);
		}
		env_tmp = env_tmp->next;
	}
	free(path_directories);
	return (NULL);
}

static void	free_str(char ***path_directories)
{
	int	array;

	array = 0;
	if ((*path_directories))
	{
		while ((*path_directories)[array])
		{
			free((*path_directories)[array]);
			array++;
		}
		free((*path_directories));
	}
}

static char	*ft_exec(char **args, t_mini *mini)
{
	t_exec_meta	d;

	d.env_tmp = mini->envpmen;
	d.path_array = get_path("PATH", d.env_tmp);
	if (!d.path_array)
		return (NULL);
	d.path_directories = ft_split(d.path_array, ':');
	free(d.path_array);
	d.array = -1;
	while (d.path_directories[++d.array] && d.path_directories)
	{
		d.path_array = ft_strjoin(d.path_directories[d.array], "/");
		d.exec = ft_strjoin(d.path_array, args[0]);
		free(d.path_array);
		if (access(d.exec, F_OK | X_OK) == 0)
		{
			free_str(&(d.path_directories));
			return (d.exec);
		}
		free(d.exec);
	}
	free_str(&(d.path_directories));
	return (NULL);
}

//an-izzzz
void	ft_nonbuiltin(char **args, t_pipelines *p, char **envp)
{
	char	*path;

	path = NULL;
	if (ft_strncmp(args[0], "./", 2) == 0 || ft_strncmp(args[0], "/", 1) == 0
		|| ft_strncmp(args[0], "../", 3) == 0)
		path = args[0];
	else
		path = ft_exec(args, p->mini);
	if (path != NULL)
	{
		reset_signal_execve();
		close_all_pipes(p->n_pipes, p->pipes);
		execve(path, args, envp);
	}
	free(path);
	close_all_pipes(p->n_pipes, p->pipes);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	p->mini->dollar_question_value = 127;
	free_args(args);
	free_pipelines(p);
	free_struc_mini(p->mini);
	exit(127);
}
