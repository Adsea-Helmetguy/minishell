/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:25:28 by mlow              #+#    #+#             */
/*   Updated: 2024/07/21 13:45:44 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	found_length_counter(char *cmd_array)
{
	int	index;
	int	found_length;

	found_length = 0;
	index = -1;
	while (cmd_array[++index])
		found_length++;
	return (found_length);
}

static void	env_update(t_env **env_tmp, char *str, t_mini *mini, int i)
{
	(*env_tmp) = string_compare(str, mini, i);
	if (*env_tmp)
		mini->total_new_length += ft_strlen((*env_tmp)->value);
}

static void	while_cmdarray(t_token **tokens, t_mini *mini, int a)
{
	int		i;
	char	*token_string;
	t_env	*env_tmp;

	i = 0;
	mini->found_length = found_length_counter(tokens[a]->string);
	while (tokens[a]->string[i])
	{
		env_tmp = mini->envpmen;
		if (tokens[a]->string[i] == '$' && tokens[a]->string[i + 1] != '\0')
		{
			i++;
			if (tokens[a]->string[i] == '?')
				mini->total_new_length += dollar_expand_question(mini);
			else if (tokens[a]->string[i])
				env_update(&env_tmp, tokens[a]->string, mini, i);
			i--;
		}
		i++;
	}
	token_string = tokens[a]->string;
	tokens[a]->string = string_duping(token_string, env_tmp, mini);
	free(token_string);
}

void	dollar_tester(t_token **tokens, t_mini *mini)
{
	int		array;

	array = -1;
	while (tokens[++array])
	{
		mini->found_length = 0;
		if (tokens[array]->token_type == TOKEN_ARG_EXPAND)
		{
			while_cmdarray(tokens, mini, array);
			if (mini && mini->dollar_string)
			{
				free(mini->dollar_string);
				mini->dollar_string = NULL;
			}
		}
		mini->total_new_length = 0;
		mini->found_length = 0;
	}
	mini->total_new_length = 0;
	mini->found_length = 0;
}
