/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:13 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 18:00:11 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	count_tokens(t_token **tokens, t_t_data *data)
{
	int	and_flag;

	data -> i = 0;
	and_flag = 0;
	while (*tokens)
	{
		data->type = (*tokens)->token_type;
		if (data->type == TOKEN_ARG_EXPAND || data->type == TOKEN_ARG_NO_EXPAND)
		{
			if (!and_flag)
				data->i++;
			else
				and_flag = 0;
		}
		else if (data->type == TOKEN_AND)
			and_flag = 1;
		else
		{
			data->i++;
			and_flag = 0;
		}
		tokens++;
	}
}

static t_token	*join_token(t_token *t1, t_token *t2)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->string = ft_strjoin(t1->string, t2->string);
	out->token_type = TOKEN_ARG_NO_EXPAND;
	free_token(t1);
	return (out);
}

static void	perform_compress(t_token **new, t_token **tokens, t_t_data *data)
{
	data->i = 0;
	data->f_and = 0;
	while (*tokens)
	{
		data->type = (*tokens)->token_type;
		if (data->type == TOKEN_ARG_EXPAND || data->type == TOKEN_ARG_NO_EXPAND)
		{
			if (!data->f_and)
				new[data->i++] = clone_token(*tokens);
			else
			{
				data->f_and = 0;
				new[data->i -1] = join_token(new[data->i -1], *tokens);
			}
		}
		else if (data->type == TOKEN_AND)
			data->f_and = 1;
		else
		{
			new[data->i++] = clone_token(*tokens);
			data->f_and = 0;
		}
		tokens++;
	}
	new[data->i] = 0;
}

t_token	**compress_tokens(t_token **tokens)
{
	t_token		**result;
	t_t_data	data;

	count_tokens(tokens, &data);
	result = malloc(sizeof(t_token *) * (data.i + 1));
	perform_compress(result, tokens, &data);
	free_tokens(tokens);
	return (result);
}
