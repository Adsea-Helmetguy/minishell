/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:47 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:48 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*clone_token(t_token *token)
{
	t_token	*result;

	result = malloc(sizeof(t_token));
	result->token_type = token->token_type;
	result->string = ft_strdup(token->string);
	return (result);
}

void	ptokens(t_token **tokens)
{
	int	index;

	index = 0;
	while (tokens[index])
	{
		printf("tokens[%d]->%s\n", index, tokens[index]->string);
		index++;
	}
}
