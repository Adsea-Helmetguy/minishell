/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:48:42 by mlow              #+#    #+#             */
/*   Updated: 2024/07/21 11:41:10 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//t_sig	g_sig;<- not allowed to do this
int	g_exit_status;

void	mini_variables_main(t_mini *mini, char **envp, int argc)
{
	if (argc > 1)
		exit(printf("Type ./minishell without any arguements\n"));
	mini->input = NULL;
	mini->pipe = 1;
	mini->total_new_length = 0;
	mini->found_length = 0;
	mini->is_it_builtin = 0;
	mini->envpmen = NULL;
	mini->environ = envp;
	mini->index = 0;
	mini->rj_i = 0;
	mini->e_i = 0;
	mini->dollar_question_value = 0;
	mini->dollar_string = NULL;
	mini->signal_fork = 0;
	define_variables(mini, envp);
}

void	killall(char *input, t_mini *mini, int while_loop)
{
	if (input)
		free(input);
	free_struc_mini(mini);
	if (while_loop == 1)
		write_main_notvalid("Exit", 2, mini->dollar_question_value);
}

int	is_empty_line(char *input)
{
	while (*input)
	{
		if ((*input < 9 || *input > 13) && *input != 32)
			return (0);
		input++;
	}
	return (1);
}

static void	process_line(t_mini *mini, char **envp)
{
	t_token	**tokens;

	if (is_empty_line(mini->input))
	{
		free(mini->input);
		return ;
	}
	tokens = lex_string(mini->input);
	free(mini->input);
	dollar_tester(tokens, mini);
	tokens = compress_tokens(tokens);
	if (execute_tokens(tokens, mini, envp))
		mini->dollar_question_value = 2;
}

//if (argc > 1)//support interactive only
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argv;
	mini_variables_main(&mini, envp, argc);
	while (1)
	{
		signal_interaction(&mini);
		mini.input = readline("Enter a command: ");
		add_history(mini.input);
		if (mini.input == NULL)
			killall(mini.input, &mini, 1);
		else if (mini.input[0] == '\0')
		{
			free(mini.input);
			continue ;
		}
		else
			process_line(&mini, envp);
	}
	killall(0, &mini, 0);
	return (0);
}
