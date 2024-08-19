/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:46 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 12:49:47 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pargs(char **args)
{
	while (*args)
		printf("%s\n", *args++);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

static void	assign_args(t_component **components, char **container)
{
	int	i;

	i = 0;
	while (components[i] && components[i]->parser_type != PARSER_PIPE)
	{
		if (components[i]->parser_type == PARSER_ARG)
			*container++ = ft_strdup(components[i]->string);
		i++;
	}
	*container = 0;
}

static int	count_args(t_component **components)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (components[i] && components[i]->parser_type != PARSER_PIPE)
	{
		if (components[i]->parser_type == PARSER_ARG)
			count++;
		i++;
	}
	return (count);
}

char	**get_args(t_component **components)
{
	char	**out;

	out = malloc(sizeof(char *) * (count_args(components) + 1));
	assign_args(components, out);
	return (out);
}
