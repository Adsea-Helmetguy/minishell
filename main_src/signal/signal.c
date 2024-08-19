/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:41:23 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 13:28:52 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_signal_execve_parent(void)
{
	struct sigaction	act_init;
	struct sigaction	act_quit;

	ft_memset(&act_init, 0, sizeof(act_init));
	act_init.sa_handler = SIG_IGN;
	sigemptyset(&act_init.sa_mask);
	sigaction(SIGINT, &act_init, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_IGN;
	sigemptyset(&act_quit.sa_mask);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	reset_signal_execve(void)
{
	struct sigaction	act_init;
	struct sigaction	act_quit;

	ft_memset(&act_init, 0, sizeof(act_init));
	act_init.sa_handler = SIG_DFL;
	sigemptyset(&act_init.sa_mask);
	sigaction(SIGINT, &act_init, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_DFL;
	sigemptyset(&act_quit.sa_mask);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	signal_reset_prompt(int signal)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = (128 + signal);
}

void	signal_interaction(t_mini *mini)
{
	struct sigaction	act;

	if (mini->signal_fork == 0)
		g_exit_status = 0;
	mini->signal_fork = 0;
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

/*
List of signals: https://man7.org/linux/man-pages/man0/signal.h.0p.html
----------------------------------------------------------
│ SIGQUIT   │       A        │ Terminal quit signal.     │
│ SIGINT    │       T        │ Terminal interrupt signal.│
----------------------------------------------------------
*/
//main minishell should ignore sig_quit 
//but child should not ignore.
