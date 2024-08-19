/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand_question.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:38:24 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 20:36:53 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar_expand_question(t_mini *mini)
{
	char	*string;
	int		string_length;
	int		dollar_after;

	string_length = 0;
	dollar_after = g_exit_status;
	if (g_exit_status == 0)
		dollar_after = mini->dollar_question_value;
	if (mini->dollar_question_value > 255)
		dollar_after %= 256;
	string = ft_itoa(dollar_after);
	string_length = ft_strlen(string);
	if (mini->dollar_string)
	{
		free(mini->dollar_string);
		mini->dollar_string = NULL;
	}
	mini->dollar_string = ft_strdup(string);
	free(string);
	return (string_length);
}
