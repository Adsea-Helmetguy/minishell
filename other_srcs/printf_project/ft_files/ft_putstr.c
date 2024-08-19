/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:13:40 by mlow              #+#    #+#             */
/*   Updated: 2023/09/27 17:13:41 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_putstr(char *s, int *count)
{
	int	index;

	if (!s)
	{
		write(1, "(null)", 6);
		(*count) = (*count) + 6;
		return ;
	}
	index = 0;
	while (s[index])
	{
		write(1, &s[index], 1);
		index++;
		(*count)++;
	}
}
//Writes out the string or (null) if char *s is NULL pointer.
