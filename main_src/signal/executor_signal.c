/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:54:54 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 14:35:25 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_fork_siginit(int signal)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = (128 + signal);
}

static void	handle_fork_sigquit(int signal)
{
	ft_putendl_fd("Quit (core dumped)", 2);
	rl_replace_line("", 0);
	g_exit_status = (128 + signal);
}

void	signal_non_interaction(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	ft_memset(&act_int, 0, sizeof(act_int));
	act_int.sa_handler = &handle_fork_siginit;
	sigemptyset(&act_int.sa_mask);
	sigaction(SIGINT, &act_int, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = &handle_fork_sigquit;
	sigemptyset(&act_quit.sa_mask);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	signal_non_interaction_parent(t_pipelines *p)
{
	struct sigaction	act_init;
	struct sigaction	act_quit;

	ft_memset(&act_init, 0, sizeof(act_init));
	if (ft_strcmp(p->components[0]->string, "./minishell") == 0)
		act_init.sa_handler = SIG_IGN;
	else
		act_init.sa_handler = &handle_fork_siginit;
	sigemptyset(&act_init.sa_mask);
	act_init.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act_init, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	if (ft_strcmp(p->components[0]->string, "./minishell") == 0)
		act_quit.sa_handler = SIG_IGN;
	else
		act_quit.sa_handler = &handle_fork_sigquit;
	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &act_quit, NULL);
}
