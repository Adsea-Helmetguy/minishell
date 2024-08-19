/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:56:44 by mlow              #+#    #+#             */
/*   Updated: 2024/07/06 10:56:48 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define PARSER_INPUT 0
# define PARSER_HEREDOC 1
# define PARSER_OUTPUT 2
# define PARSER_APPEND 3
# define PARSER_ARG 4
# define PARSER_PIPE 5

# define EXPECT_NOTHING 0
# define EXPECT_ARG 1
# define EXPECT_NOT_PIPE 2

typedef struct s_component
{
	int		parser_type;
	char	*string;
}	t_component;

typedef struct s_count_meta
{
	int	count;
	int	expectation;
}	t_count_meta;

typedef struct s_assign_meta
{
	int			i;
	int			expectation;
	int			prev_type;
	t_component	**components;
}	t_assign_meta;

// parser.c
t_component	**parse_tokens(t_token **tokens);
// parser_utils.c
int			is_arg(t_token *token);
int			token_expectation(t_token *token);
int			map_token_to_type(t_token *token);
// parser_utils2.c
int			count_components(t_token **tokens);
// component_free.c
void		free_component(t_component *component);
void		free_components(t_component **components);

#endif
