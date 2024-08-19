/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:36:58 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 14:14:33 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../other_srcs/libft_project/libft.h"
# include "../other_srcs/printf_project/libftprintf.h"
# include "../other_srcs/get_next_line_project/get_next_line_bonus.h"
# include "parser.h"
# include "executor.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{
	char			**user_value;
	char			*name;
	char			*value;
	int				env_equal;
	struct s_env	*next;
}		t_env;

typedef struct s_mini
{
	t_env			*envpmen;
	char			**environ;
	int				index;
	int				rj_i;
	int				e_i;
	char			*input;
	int				total_new_length;
	int				found_length;
	int				dollar_question_value;
	char			*dollar_string;
	int				is_it_builtin;
	int				pipe;
	int				infile;
	int				outfile;
	int				no_exec;
	int				signal_fork;
}				t_mini;

typedef struct s_exec_meta
{
	int		array;
	char	*path_array;
	char	**path_directories;
	char	*exec;
	t_env	*env_tmp;
}	t_exec_meta;

//global variable
extern int	g_exit_status;
//main.c (to init the values)
void	mini_variables_main(t_mini *mini, char **envp, int argc);
//dollar_checker.c
int		dollar_name(char *cmd, t_env *e, t_mini *mini, int i);
//void	while_cmdarrayindex(char **cmd, t_mini *mini, int a);
void	while_cmdarrayindex(t_token **tokens, t_mini *mini, int a);
//
//dollar file!!
char	*string_duping(char *cmd_array, t_env *e, t_mini *mini);
void	dollar_tester(t_token **tokens, t_mini *mini);
int		dollar_expand_question(t_mini *mini);
//
//signal.c
void	reset_signal_execve(void);
void	reset_signal_execve_parent(void);
void	signal_reset_prompt(int signal);
void	signal_interaction(t_mini *mini);
//executor_signal.c
void	signal_non_interaction(void);
void	signal_non_interaction_parent(t_pipelines *pipelines);
//heredoc_signal.c
void	heredoc_child_signal(void);
void	heredoc_parent_signal(void);
//env.c
void	mini_environ_env(t_mini *mini, char **envp);
//builtin.c
void	define_variables(t_mini *mini, char **envp);
void	*ft_builtin(char **args, t_mini *mini);
void	*ft_others(char **args, int n_pipes, t_mini *mini);
//
//--------------------------------------------------------------
//void	*ft_builtin(t_component **components, t_mini *mini);
//echo_function.c
void	echo_function(int length, char **args, t_mini *mini);
//cd_function.c
void	cd_function(int l, char **args, t_mini *mini);
//pwd_function.c
void	pwd_function(t_mini *mini);
//export_tester.c
void	export_function(int l, char **args, t_env *envp, t_mini *mini);
//env_function.c
void	env_function(int length, char **args, t_mini *mini);
//unset_function.c
void	unset_function(int l, char **args, t_env **envp, t_mini *mini);
//exit_function.c
int		exit_function(char **args, t_mini *mini);
//builtin-end-
//--------------------------------------------------------------
//
//----------------------------------------------------------
//ft_notbuiltin.c
void	ft_nonbuiltin(char **args, t_pipelines *p, char **envp);
//nonbuiltin_or_builtin.c
void	builtin_or_not(char **cmds, t_pipelines *p, char **envp);
//-if_notbuiltin.c ends-
//----------------------------------------------------------
//
//---------------
//@utils_file
int		ft_strcmp(char *s1, char *s2);
int		d_strncmp(char *s1, char *s2, size_t n, int index);
t_env	*ftps_lstlast(t_env *lst);
void	ftps_lstadd_back(t_env **lst, t_env *new);
char	**ft_split_export(char const *s, char c);
//index_quotes_helper.c
int		index_helper(char *cmd_array, int index);
int		invalid_char(char *cmd_array, int index);
//export_helper.c
t_env	*ft_sort_list(t_env *e);
//freeing_struc
void	ftps_free(char **to_free);
void	free_env(t_mini *mini);
void	free_struc_mini(t_mini *mini);
//ft_split
//helper for d_strncmp
t_env	*string_compare(char *cmd_array, t_mini *mini, int i);
//write_helper.c
void	write_export_notvalid(char *msg, t_mini *m, char ***name);
void	write_cd_notvalid(char *string, t_mini *mini);
void	write_exit_notvalid(char **str, char *msg, int fd, t_mini *mini);
void	write_main_notvalid(char *msg, int fd, int exit);
//utils-end-
//--------------
#endif
/*
#include <unistd.h> // for fork() / execve() / access()
#include <stdio.h> // for printf()
#include <stdlib.h> // exit()
#include <fcntl.h> //open()
#include <sys/wait.h> // wait() / waitpid()
#include <sys/types.h> //for wait() / fork() / pid_t() / wait() / waitpid() 
#include <errno.h> // for perror()
#include <stdbool.h> // for bool
#include <pthread.h> // for defining   include ""sys/types.h""?
#include <sys/time.h> // for using gettimeofday()
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
For minishell:
#include <stdio.h>/<readline/readline.h>/<readline/history.h>
*/
