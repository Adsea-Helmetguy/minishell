/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:50:49 by mlow              #+#    #+#             */
/*   Updated: 2024/03/13 21:51:19 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//@ line 30, should use ft_strcmp?
static int	update_pwd(t_mini *mini)
{
	char	*cwd;
	t_env	*env;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return (0);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	env = mini->envpmen;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "PWD", 3) == 0)
		{
			free(env->value);
			env->value = NULL;
			env->value = ft_strdup(cwd);
		}
		env = env->next;
	}
	free(cwd);
	return (1);
}

//@ line 58, should use ft_strcmp?
static int	update_oldpwd(t_mini *mini)
{
	char	*cwd;
	t_env	*env;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return (0);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	env = mini->envpmen;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = NULL;
			env->value = ft_strdup(cwd);
		}
		env = env->next;
	}
	free(cwd);
	return (1);
}

static char	*ft_getenv(char *directory, t_mini *mini)
{
	t_env	*env;

	env = mini->envpmen;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, directory) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

static void	perform_cd(int l, char **args, t_mini *mini)
{
	const char	*home_dir;

	update_oldpwd(mini);
	mini->dollar_question_value = 0;
	if ((l == 1) || ft_strcmp(args[1], "~") == 0)
	{
		home_dir = ft_getenv("HOME", mini);
		if (home_dir == NULL || (chdir(home_dir) != 0))
			write_cd_notvalid("HOME not set", mini);
		update_pwd(mini);
	}
	else if (l == 2 && args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
		{
			write_cd_notvalid("no such file or directory.", mini);
			return ;
		}
		update_pwd(mini);
	}
}

void	cd_function(int l, char **args, t_mini *mini)
{
	mini->dollar_question_value = 1;
	if (l < 3)
		perform_cd(l, args, mini);
	else
		write_cd_notvalid("too many arguments", mini);
}
