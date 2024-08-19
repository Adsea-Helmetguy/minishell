/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:43 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:44 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	free_token(t_token *token)
{
	if (token->string)
		free(token->string);
	free(token);
}

void	free_tokens(t_token **tokens)
{
	int	index;

	index = 0;
	while (tokens[index])
		free_token(tokens[index++]);
	free(tokens);
}
