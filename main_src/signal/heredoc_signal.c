/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:16:21 by mlow              #+#    #+#             */
/*   Updated: 2024/07/08 14:25:00 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_child(int signal)
{
	int	status;

	status = 0;
	rl_on_new_line();
	rl_redisplay();
	ft_putendl_fd("^C", 2);
	status = (128 + signal);
	exit(status);
}

void	heredoc_child_signal(void)
{
	struct sigaction	act_init;
	struct sigaction	act_quit;

	ft_memset(&act_init, 0, sizeof(act_init));
	act_init.sa_handler = &heredoc_child;
	sigemptyset(&act_init.sa_mask);
	sigaction(SIGINT, &act_init, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_IGN;
	sigemptyset(&act_quit.sa_mask);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	heredoc_parent_signal(void)
{
	struct sigaction	act_init;
	struct sigaction	act_quit;

	ft_memset(&act_init, 0, sizeof(act_init));
	act_init.sa_handler = SIG_IGN;
	sigemptyset(&act_init.sa_mask);
	act_init.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act_init, NULL);
	ft_memset(&act_quit, 0, sizeof(act_quit));
	act_quit.sa_handler = SIG_IGN;
	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &act_quit, NULL);
}
