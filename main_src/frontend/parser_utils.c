/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:35 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:36 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_arg(t_token *token)
{
	return (token->token_type == TOKEN_ARG_EXPAND
		|| token->token_type == TOKEN_ARG_NO_EXPAND);
}

int	token_expectation(t_token *token)
{
	int	type;

	type = token->token_type;
	if (type == TOKEN_REDIR_FROM || type == TOKEN_HERE_DOCUMENT
		|| type == TOKEN_REDIR_TO || type == TOKEN_APPEND_TO)
		return (EXPECT_ARG);
	if (type == TOKEN_PIPE)
		return (EXPECT_NOT_PIPE);
	return (EXPECT_NOTHING);
}

int	map_token_to_type(t_token *token)
{
	int	type;

	type = token->token_type;
	if (type == TOKEN_REDIR_FROM)
		return (PARSER_INPUT);
	else if (type == TOKEN_HERE_DOCUMENT)
		return (PARSER_HEREDOC);
	else if (type == TOKEN_REDIR_TO)
		return (PARSER_OUTPUT);
	else if (type == TOKEN_APPEND_TO)
		return (PARSER_APPEND);
	return (-1);
}
