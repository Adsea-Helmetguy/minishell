/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:35 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:33:36 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	count_expect_nothing(t_token **tokens, t_count_meta *d)
{
	if (is_arg(*tokens) || (*tokens)->token_type == TOKEN_PIPE)
		d->count = d->count + 1;
	d->expectation = token_expectation(*tokens);
}

static void	init_count_meta(t_count_meta *d)
{
	d->count = 0;
	d->expectation = EXPECT_NOT_PIPE;
}

static void	count_expect_arg(t_count_meta *d)
{
	d->expectation = EXPECT_NOTHING;
	d->count = d->count + 1;
}

// returns -1 if syntax error
int	count_components(t_token **tokens)
{
	t_count_meta	d;

	init_count_meta(&d);
	while (*tokens)
	{
		if (d.expectation == EXPECT_ARG)
		{
			if (!is_arg(*tokens))
				return (-1);
			count_expect_arg(&d);
		}
		else if (d.expectation == EXPECT_NOT_PIPE)
		{
			if ((*tokens)->token_type == TOKEN_PIPE)
				return (-1);
			d.expectation = EXPECT_NOTHING;
			continue ;
		}
		else
			count_expect_nothing(tokens, &d);
		tokens++;
	}
	if (d.expectation)
		return (-1);
	return (d.count);
}
