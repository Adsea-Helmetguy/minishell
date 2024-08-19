/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:28:14 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:19 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	get_type(char c1, char c2)
{
	if (c1 == '|')
		return (TOKEN_PIPE);
	else if (c1 == '>' && c2 == '>')
		return (TOKEN_APPEND_TO);
	else if (c1 == '>' && c2 != '>')
		return (TOKEN_REDIR_TO);
	else if (c1 == '<' && c2 != '<')
		return (TOKEN_REDIR_FROM);
	else if (c1 == '<' && c2 == '<')
		return (TOKEN_HERE_DOCUMENT);
	return (-1);
}

void	determine_special_char(t_token_data *d, int len, t_token **t)
{
	char	c1;
	char	c2;

	c1 = d->str[d->i];
	c2 = d->str[d->i +1];
	if (d->i + 1 < len && d->str[d->i] == d->str[d->i +1]
		&& d->str[d->i] == '>')
	{
		d->i++;
		c1 = '>';
		c2 = '>';
	}
	else if (d->i + 1 < len && d->str[d->i] == d->str[d->i +1]
		&& d->str[d->i] == '<')
	{
		d->i++;
		c1 = '<';
		c2 = '<';
	}
	d->i++;
	*(t + d->offset++) = get_t(d->str, d->start, d->i, get_type(c1, c2));
}

void	get_tokens_handle_special_after(t_token **t, t_token_data *d, int len)
{
	while (d->i < len && d->str[d->i] != ' '
		&& !lexer_is_special_char(d->str[d->i]))
		d->i++;
	if (d->i < len && lexer_is_special_char(d->str[d->i]))
	{
		*(t + d->offset++) = get_t(d->str, d->start, d->i, TOKEN_ARG_EXPAND);
		if (lexer_is_quotes(d->str[d->i]))
			*(t + d->offset++) = get_t(0, 0, 0, TOKEN_AND);
		d->i--;
	}
	else if (d->start != d->i)
		*(t + d->offset++) = get_t(d->str, d->start, d->i, TOKEN_ARG_EXPAND);
	d->i++;
}

void	get_tokens(t_token **t, char *str)
{
	t_token_data	d;
	int				len;

	init_tokenization_data(&d, str);
	len = lexer_length(str);
	while (d.i < len)
	{
		all_bounded_by_append(&d, t);
		while (d.i < len && str[d.i] == ' ')
			d.i++;
		d.start = d.i;
		if (d.i < len && lexer_is_quotes(str[d.i]))
			continue ;
		if (d.i < len && lexer_is_special_char(str[d.i]))
		{
			determine_special_char(&d, len, t);
			continue ;
		}
		get_tokens_handle_special_after(t, &d, len);
	}
	*(t + d.offset) = 0;
}

// 1. get_tokens -> tokenizes
// 2. compress_tokens -> call after expanding. combines strings separated by AND
t_token	**lex_string(char *str)
{
	t_token	**tokens;

	tokens = malloc((1 + lex_token_count(str)) * sizeof(t_token *));
	get_tokens(tokens, str);
	return (tokens);
}
