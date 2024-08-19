/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_d_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:05:45 by mlow              #+#    #+#             */
/*   Updated: 2024/04/28 16:06:08 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//echo "HIhoiasjauisdhaos $USERASUHI aoisdhoihduio $HOME"
int	index_helper(char *cmd_array, int index)
{
	while (cmd_array[index] != '\0' && cmd_array[index] != '_'
		&& ((cmd_array[index] >= 'a' && cmd_array[index] <= 'z')
			|| (cmd_array[index] >= 'A' && cmd_array[index] <= 'Z')
			|| (cmd_array[index] >= '0' && cmd_array[index] <= '9')))
		index++;
	return (index);
}

int	invalid_char(char *cmd_array, int index)
{
	if (cmd_array[index] == '\0'
		|| ((cmd_array[index] < 'a' || cmd_array[index] > 'z')
			&& (cmd_array[index] < 'A' || cmd_array[index] > 'Z')
			&& (cmd_array[index] < '0' || cmd_array[index] > '9')
			&& cmd_array[index] != '_'))
		return (0);
	return (1);
}
