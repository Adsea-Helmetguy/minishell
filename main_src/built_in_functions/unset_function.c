/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:39:51 by mlow              #+#    #+#             */
/*   Updated: 2024/03/25 18:41:38 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	unset_first(char *arg, char *n, t_env **env, t_env **envp)
{
	if (ft_strncmp(arg, n, ft_strlen(n)) == 0)
	{
		*env = (*envp)->next;
		if ((*envp)->user_value)
			ftps_free((*envp)->user_value);
		if ((*envp)->name)
			free((*envp)->name);
		if ((*envp)->value)
			free((*envp)->value);
		free((*envp));
		(*envp) = NULL;
		*envp = *env;
		return (0);
	}
	return (1);
}

static int	unset_others(char *arg, t_env **env)
{
	t_env	*env_t;

	if (ft_strncmp(arg, (*env)->next->name
			, ft_strlen((*env)->next->name)) == 0)
	{
		env_t = (*env)->next->next;
		if (!(*env)->next->next)
			env_t = NULL;
		if ((*env)->next)
		{
			if ((*env)->next->user_value)
				ftps_free((*env)->next->user_value);
			if ((*env)->next->name)
				free((*env)->next->name);
			if ((*env)->next->value)
				free((*env)->next->value);
			free((*env)->next);
			(*env)->next = NULL;
		}
		(*env)->next = env_t;
		return (0);
	}
	return (1);
}

void	unset_function(int l, char **args, t_env **envp, t_mini *mini)
{
	t_env	*env;
	int		ay;

	mini->dollar_question_value = 0;
	env = *envp;
	if (!(args[1]) || envp == NULL || !envp)
		return ;
	ay = 0;
	while (++ay < l)
	{
		if (unset_first(args[ay], env->name, &env, envp) == 0)
			continue ;
		while (env && env->next)
		{
			if (unset_others(args[ay], &env) == 0)
				break ;
			env = env->next;
		}
		env = (*envp);
	}
}
