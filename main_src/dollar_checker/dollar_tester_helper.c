/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tester_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <mlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:31:33 by mlow              #+#    #+#             */
/*   Updated: 2024/07/18 20:42:23 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_malloc(t_mini *mini)
{
	char	*replace_join;

	mini->index = mini->total_new_length + mini->found_length;
	replace_join = malloc(sizeof(char) * (mini->index + 1));
	mini->index = 0;
	mini->rj_i = 0;
	replace_join[0] = '\0';
	return (replace_join);
}

static void	sd_helper(t_env **e, char **replace_join,
			char *cmd_array, t_mini *mini)
{
	if (cmd_array[mini->index])
		(*e) = string_compare(cmd_array, mini, mini->index);
	if ((*e) != NULL)
	{
		while ((*e)->value && (*e)->value[mini->e_i])
			(*replace_join)[mini->rj_i++] = (*e)->value[mini->e_i++];
		mini->index += ft_strlen((*e)->name);
	}
	else
		mini->index = index_helper(cmd_array, mini->index);
}

static void	update_replace(char **r_j, t_mini *mini)
{
	while (mini->dollar_string && mini->dollar_string[mini->e_i])
		(*r_j)[mini->rj_i++] = mini->dollar_string[mini->e_i++];
	mini->index++;
}

char	*string_duping(char *cmd_array, t_env *e, t_mini *mini)
{
	char	*replace_join;

	replace_join = replace_malloc(mini);
	while (cmd_array[mini->index])
	{
		mini->e_i = 0;
		if (cmd_array[mini->index] == '$')
		{
			if (cmd_array[++(mini->index)] == '?')
			{
				update_replace(&replace_join, mini);
				continue ;
			}
			else if (cmd_array[mini->index] == '\0')
			{
				replace_join[mini->rj_i++] = '$';
				continue ;
			}
			sd_helper(&e, &replace_join, cmd_array, mini);
		}
		else
			replace_join[mini->rj_i++] = cmd_array[mini->index++];
	}
	replace_join[mini->rj_i] = '\0';
	return (replace_join);
}
