/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:28:14 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:19 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*get_t(char *s, int from, int to, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (s)
		token->string = lexer_str_dup(s + from, to - from);
	else
		token->string = 0;
	token->token_type = type;
	return (token);
}

void	bounded_by(char b, t_token_data *data)
{
	data->i++;
	data->start = data->i;
	while (data->str[data->i] && data->str[data->i] != b)
		data->i++;
	data->offset++;
	if (data->i +1 < lexer_length(data->str)
		&& !lexer_is_exclude_chars(data->str[data->i +1]))
		data->offset++;
	data->i++;
}

void	all_bounded_by(t_token_data *data)
{
	if (data->str[data->i] == '"')
		bounded_by('"', data);
	else if (data->str[data->i] == '\'')
		bounded_by('\'', data);
}

void	b_by_append(char b, t_token_data *data, t_token **tokens, int type)
{
	t_token	*token;

	data->i++;
	data->start = data->i;
	while (data->str[data->i] && data->str[data->i] != b)
		data->i++;
	token = get_t(data->str, data->start, data->i, type);
	*(tokens + data->offset++) = token;
	if (data->i +1 < lexer_length(data->str)
		&& !lexer_is_exclude_chars(data->str[data->i +1]))
		*(tokens + data->offset++) = get_t(0, 0, 0, TOKEN_AND);
	data->i++;
}

void	all_bounded_by_append(t_token_data *data, t_token **tokens)
{
	if (data->str[data->i] == '"')
		b_by_append('"', data, tokens, TOKEN_ARG_EXPAND);
	else if (data->str[data->i] == '\'')
		b_by_append('\'', data, tokens, TOKEN_ARG_NO_EXPAND);
}
