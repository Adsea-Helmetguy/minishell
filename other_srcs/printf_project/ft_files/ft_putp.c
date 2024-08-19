/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:14:05 by mlow              #+#    #+#             */
/*   Updated: 2023/09/30 16:19:15 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	ft_pworking(unsigned long nb, char *base, int *count)
{
	int	p;

	if (nb > 15)
		ft_pworking((nb / 16), base, count);
	p = base[(nb % 16)];
	ft_putc(p, count);
}

void	ft_putp(unsigned long nb, char *base, int *count)
{
	if (!nb)
	{
		write(1, "(nil)", 5);
		(*count) = (*count) + 5;
		return ;
	}
	else
	{
		write(1, "0x", 2);
		(*count) = (*count) + 2;
		ft_pworking(nb, base, count);
	}
}
//s = base[(nb % 16)];//the position of base[] = "0123456789abcdef"
//
//Now we go through the next thing, which is ft_putp.
// Just noting, we don't really need a static function?
// We could write a int value and if its '0' it will print
// out "0x" instead of using helper function to do so.
//
// This is neat through so no worries.
//
//Firstly, we start with ft_putp. "unsigned long nb"
// is from testcase "s1". "*base" is a string with
// the values: "0123456789abcdef" & count.
//
//if nb is not true/ reads null, it will write 
// "(nil)" before breaking the function with return.
// Reason is because if you tested it out with 
// the actual printf, you will know as they will
// print that if its NULL.
//ELSE
//write "0x" then increase count by 2. Followed by
// the next one, ft_pworking XD.
//
//It will convert the values into hex by dividing it
// by 16 first, then '%' them to get the value of the
// memory address with putc.
// it will come back to ft_putp and ends the loop.
