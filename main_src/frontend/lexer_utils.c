/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:02:18 by keyu              #+#    #+#             */
/*   Updated: 2024/05/12 13:02:20 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	lexer_is_special_char(char c)
{
	return (c == '|' || c == '>'
		|| c == '<' || c == '"' || c == '\'');
}

int	lexer_is_quotes(char c)
{
	return (c == '"' || c == '\'');
}

// for consideration on whether the next character
// following a quote should be part of "AND"
int	lexer_is_exclude_chars(char c)
{
	return (c == '>' || c == '<' || c == '|'
		|| (c >= 9 && c <= 13) || c == ' ');
}

int	lexer_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*lexer_str_dup(char *s, int count)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((1 + count) * sizeof(char));
	while (i < count)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
