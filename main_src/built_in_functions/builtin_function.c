/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:12:57 by mlow              #+#    #+#             */
/*   Updated: 2024/06/29 14:29:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	lenstr(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	define_variables(t_mini *mini, char **envp)
{
	int		index;
	t_env	*env_tmp;

	env_tmp = mini->envpmen;
	index = -1;
	while (envp[++index])
	{
		if (env_tmp == NULL)
			env_tmp = malloc(sizeof(t_env) * (1));
		env_tmp->user_value = ft_split(envp[index], '=');
		env_tmp->name = ft_strdup(env_tmp->user_value[0]);
		env_tmp->value = ft_strdup(env_tmp->user_value[1]);
		env_tmp->env_equal = 0;
		if (lenstr(env_tmp->user_value) > 1)
			env_tmp->env_equal = 1;
		env_tmp->next = NULL;
		ftps_lstadd_back(&mini->envpmen, env_tmp);
		env_tmp = env_tmp->next;
	}
	env_tmp = mini->envpmen;
}

void	*ft_builtin(char **args, t_mini *mini)
{
	int	length;

	length = 0;
	while (args[length])
		length++;
	if (args[0] == NULL)
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		echo_function(length, args, mini);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd_function(mini);
	else if (ft_strcmp(args[0], "export") == 0)
		return (0);
	else if (ft_strcmp(args[0], "env") == 0)
		env_function(length, args, mini);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (0);
	else
		mini->is_it_builtin = 0;
	return (0);
}

void	*ft_others(char **args, int n_pipes, t_mini *mini)
{
	int	length;

	length = 0;
	while (args[length])
		length++;
	mini->is_it_builtin = 1;
	if (ft_strcmp(args[0], "cd") == 0 && n_pipes == 0)
		cd_function(length, args, mini);
	else if (ft_strcmp(args[0], "export") == 0)
	{
		mini->dollar_question_value = 0;
		export_function(length, args, mini->envpmen, mini);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
		unset_function(length, args, &mini->envpmen, mini);
	else
		mini->is_it_builtin = 0;
	return (0);
}
//
//
/*
readline: Reads a line of text from the standard input.
" provides features such as line editing 
(e.g., editing text using arrow keys), 
history support (keeping track of previously entered commands), 
and completion (suggesting completions for partially typed commands)."

rl_clear_history: Clears the history list maintained by the readline library.

rl_on_new_line: Signals readline that you are starting a new line.

rl_replace_line: Replaces the current line of input in the 
readline buffer with the given text.

rl_redisplay: Forces readline to redraw the current input line.

add_history: Adds a line to the readline history.

printf: Writes formatted output to stdout.

malloc: Allocates memory dynamically.

free: Frees dynamically allocated memory.

write: Writes data to a file descriptor.

access: Checks whether a file can be accessed with the 
specified permissions.

open: Opens a file or device.

read: Reads data from a file descriptor.

close: Closes a file descriptor.

fork: Creates a new process by duplicating the current process.

wait, waitpid, wait3, wait4: Wait for a child process to terminate.

signal, sigaction: Sets signal handling for specific signals.

sigemptyset, sigaddset: Functions for manipulating signal sets.

kill: Sends a signal to a process.

exit: Exits the current process.

getcwd: Gets the current working directory.

chdir: Changes the current working directory.

stat, lstat, fstat: Retrieves file status information.

unlink: Removes a file from the filesystem.

execve: Executes a program.

dup, dup2: Duplicates a file descriptor.

pipe: Creates a pipe.

opendir, readdir, closedir: Functions for working with directories.

strerror: Returns a string describing the error code.

perror: Prints a descriptive error message to stderr.

isatty: Checks if a file descriptor refers to a terminal.

ttyname: Returns the name of the terminal associated 
with a file descriptor.

ttyslot: Returns the slot number of the current user's 
terminal in the user database.

ioctl: Performs I/O control operations on devices.

getenv: Retrieves the value of an environment variable.

tcsetattr, tcgetattr: Sets and gets terminal attributes.

tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs: 
Functions for accessing termcap/terminfo database for terminal control.
*/
//
