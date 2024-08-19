/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:13:46 by mlow              #+#    #+#             */
/*   Updated: 2023/09/30 16:00:55 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_putdi(int nb, int *count)
{
	int	s;

	if (nb == 0)
	{
		write (1, "0", 1);
		(*count)++;
		return ;
	}
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) = (*count) + 11;
		return ;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
		(*count)++;
	}
	if (nb > 9)
		ft_putdi((nb / 10), count);
	s = (nb % 10) + '0';
	ft_putc(s, count);
}
//The idea is to read both 'd' & 'i'.
//However, since both are the same
// in the printf function, we can put
// both in the same function. 
//
//Both 'd' & 'i' handles the base 10.
// we use void to handle the working
// since back at "ft_printf", we just
// wrote "ft_convert" which is just
// a working to increase count.
//
//We handled the following, 
// 1)if its 0,
// 2) if its INT_MIN
// 3) if its less than 0
// 4) if its more than 9.
//
// i wont explain 1-3 since they are
// quite easy to explain right?
//
// 4) Once nb is read and it's value is 
// more than 9, we call back the function
// "ft_putdi" and returning "int nb" as
// a divided value which will keep doing so
// until it is no longer more than 9.
//
// For example, 1119. it will divide by 10
// to give 111, then 11, then 1.
// Then with 1, we will first '%' it by 10.
// Giving it a remainder of 1. Using ft_putc,
// we write the function and go back to 11.
//
// 11 will then '%' by 10. Which return 1.
// Giving it a remainder of 1. Then putc.
//
// 111 then 1119. for 1119, we Modulo it 
// by 10. which will give remainder of 9.
//
// then putc the final value. Thus it will
// print out 1119 in character one by one.
