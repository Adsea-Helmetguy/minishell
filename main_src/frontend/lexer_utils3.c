/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:28:14 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:19 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	init_tokenization_data(t_token_data *data, char *str)
{
	data -> i = 0;
	data -> start = 0;
	data -> str = str;
	data -> offset = 0;
}

void	lex_token_count_special_char(t_token_data *data, int len)
{
	if (data->i +1 < len && data->str[data->i] == data->str[data->i +1]
		&& data->str[data->i] == '>')
		data->i++;
	else if (data->i +1 < len && data->str[data->i] == data->str[data->i +1]
		&& data->str[data->i] == '<')
		data->i++;
	data->i++;
	data->offset++;
}

void	lex_token_count_special_char_after(t_token_data *data, int len)
{
	while (data->i < len && data->str[data->i] != ' '
		&& !lexer_is_special_char(data->str[data->i]))
		data->i++;
	if (data->i < len && lexer_is_special_char(data->str[data->i]))
	{
		data->offset++;
		if (lexer_is_quotes(data->str[data->i]))
			data->offset++;
		data->i--;
	}
	else if (data->start != data->i)
		data->offset++;
}

int	lex_token_count(char *str)
{
	int				len;
	t_token_data	data;

	init_tokenization_data(&data, str);
	len = lexer_length(str);
	while (data.i < len)
	{
		all_bounded_by(&data);
		while (data.i < len && data.str[data.i] == ' ')
			data.i++;
		data.start = data.i;
		if (data.i < len && lexer_is_quotes(str[data.i]))
			continue ;
		if (data.i < len && lexer_is_special_char(str[data.i]))
		{
			lex_token_count_special_char(&data, len);
			continue ;
		}
		lex_token_count_special_char_after(&data, len);
		data.i++;
	}
	return (data.offset);
}
