/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:13:53 by mlow              #+#    #+#             */
/*   Updated: 2023/09/27 17:13:54 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_putu(unsigned int nb, int *count)
{
	int	s;

	if (nb == 0)
	{
		write (1, "0", 1);
		(*count)++;
		return ;
	}
	if (nb > 9)
	{
		ft_putu((nb / 10), count);
	}
	s = (nb % 10) + '0';
	ft_putc(s, count);
}
//its bascially putdi version of putnbr but as unsigned int.
// same shit bascially. Just no less than 0s.
