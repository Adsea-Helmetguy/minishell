/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:35 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:36 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_component	*get_component(t_token *token)
{
	t_component	*component;

	component = malloc(sizeof(t_component));
	if (token->token_type == TOKEN_PIPE)
	{
		component->string = 0;
		component->parser_type = PARSER_PIPE;
	}
	else if (is_arg(token))
	{
		component->string = ft_strdup(token->string);
		component->parser_type = PARSER_ARG;
	}
	return (component);
}

static t_component	*get_expected(t_token *curr, int prev_type)
{
	t_component	*component;

	component = malloc(sizeof(t_component));
	component->string = ft_strdup(curr->string);
	component->parser_type = prev_type;
	return (component);
}

void	init_assign_comps(t_assign_meta *data, t_component **components)
{
	data->i = 0;
	data->expectation = EXPECT_NOT_PIPE;
	data->components = components;
}

static void	assign_components(t_component **components, t_token **tokens)
{
	t_assign_meta	d;

	init_assign_comps(&d, components);
	while (*tokens)
	{
		if (d.expectation == EXPECT_ARG)
		{
			components[d.i++] = get_expected(*tokens, d.prev_type);
			d.expectation = EXPECT_NOTHING;
		}
		else if (d.expectation == EXPECT_NOT_PIPE)
		{
			d.expectation = EXPECT_NOTHING;
			continue ;
		}
		else
		{
			if (is_arg(*tokens) || (*tokens)->token_type == TOKEN_PIPE)
				components[d.i++] = get_component(*tokens);
			d.expectation = token_expectation(*tokens);
			d.prev_type = map_token_to_type(*tokens);
		}
		tokens++;
	}
	components[d.i] = 0;
}

// groups tokens into components
// a component is a set of operator + string
// except for when operator is PIPE, then string is null
t_component	**parse_tokens(t_token **tokens)
{
	t_component	**components;
	int			component_count;

	component_count = count_components(tokens);
	if (component_count == -1)
		return (0);
	components = malloc(sizeof(t_component *) * (component_count + 1));
	assign_components(components, tokens);
	return (components);
}
