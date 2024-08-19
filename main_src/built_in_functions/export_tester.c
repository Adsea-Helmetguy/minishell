/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:16:49 by mlow              #+#    #+#             */
/*   Updated: 2024/04/14 17:17:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

		/*
		if (env_tmp->value)
			printf("=\"%s\"\n", env_tmp->value);
		else if (env_tmp->env_equal == 1)
			printf("=\n");
		else
			printf("\n");
		*/
static void	declare_x_export(t_env *envpmen)
{
	t_env	*env_tmp;
	t_env	*env_savefile;

	env_tmp = ft_sort_list(envpmen);
	env_savefile = env_tmp;
	while (env_tmp != NULL)
	{
		printf("declare -x %s", env_tmp->name);
		if (env_tmp->env_equal == 1)
			printf("=\"");
		if (env_tmp->value)
			printf("%s", env_tmp->value);
		if (env_tmp->env_equal == 1)
			printf("\"\n");
		else
			printf("\n");
		env_tmp = env_tmp->next;
	}
	env_tmp = env_savefile;
}

static int	e_ch(char *name_array)
{
	int	checker;

	checker = -1;
	if (!name_array)
		return (0);
	while (name_array[++checker])
	{
		if (invalid_char(name_array, checker) == 0)
		{
			return (1);
		}
	}
	return (0);
}

static void	export_quote_helper(char **name, t_env **env_tmp, char *args_ay)
{
	if ((*env_tmp))
	{
		if ((*env_tmp)->user_value)
			ftps_free((*env_tmp)->user_value);
		(*env_tmp)->user_value = name;
		if ((*env_tmp)->name)
		{
			free((*env_tmp)->name);
			(*env_tmp)->name = NULL;
		}
		if ((*env_tmp)->value && ft_strchr(args_ay, '=') != NULL)
		{
			free((*env_tmp)->value);
			(*env_tmp)->value = NULL;
		}
	}
	if ((*env_tmp) == NULL)
	{
		(*env_tmp) = malloc(sizeof(t_env) * (1));
		(*env_tmp)->next = NULL;
		(*env_tmp)->user_value = NULL;
		(*env_tmp)->name = NULL;
		(*env_tmp)->value = NULL;
		(*env_tmp)->env_equal = 0;
	}
}

//freeing the "name"&&"value" of the env if it exist, add the new one in.
static void	export_quote(char **name, char **args, t_mini *mini, int ay)
{
	t_env	*env_tmp;

	env_tmp = mini->envpmen;
	while (env_tmp && ft_strcmp(name[0], env_tmp->name) != 0)
		env_tmp = env_tmp->next;
	export_quote_helper(name, &env_tmp, args[ay]);
	env_tmp->name = ft_strdup(name[0]);
	if (name[1] && (!(env_tmp->value)))
		env_tmp->value = ft_strdup(name[1]);
	if (ft_strchr(args[ay], '=') != NULL || env_tmp->env_equal == 1)
		env_tmp->env_equal = 1;
	else if (ft_strchr(args[ay], '=') == NULL)
		env_tmp->env_equal = 0;
	if (env_tmp->next == NULL)
	{
		ftps_lstadd_back(&mini->envpmen, env_tmp);
		if (env_tmp->user_value == NULL)
			env_tmp->user_value = name;
		env_tmp->next = NULL;
	}
}

void	export_function(int l, char **args, t_env *envp, t_mini *mini)
{
	char	**name;
	int		a;

	a = 0;
	if (l > 1)
	{
		while (++a < l)
		{
			if (ft_isdigit(args[a][0]) > 0 || args[a][0] == '=')
			{
				write_export_notvalid(args[a], mini, NULL);
				continue ;
			}
			name = ft_split_export(args[a], '=');
			if (name == NULL || !name[0] || !name[0][0] || (e_ch(name[0]) == 1))
			{
				write_export_notvalid(args[a], mini, &name);
				return ;
			}
			export_quote(name, args, mini, a);
		}
	}
	else if (envp != NULL || envp)
		declare_x_export(envp);
}
