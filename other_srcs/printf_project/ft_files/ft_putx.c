/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:13:59 by mlow              #+#    #+#             */
/*   Updated: 2023/09/27 17:13:59 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_putx(unsigned int nb, char *base, int *count)
{
	int	x;

	if (nb > 15)
	{
		ft_putx((nb / 16), base, count);
	}
	x = base[(nb % 16)];
	ft_putc(x, count);
}
//s = base[(nb % 16)];//the position of base[] = "0123456789abcdef"
//
//Firstly, we start with ft_putx. "unsigned long nb"
// is from testcase "s1". "*base" is a string with
// the values: "0123456789abcdef" & count.
//
//
//It will convert the values into hex by dividing it
// by 16 first, then '%' them to get the value of the
// memory address with putc.
// it will come back to ft_putp and ends the loop.
