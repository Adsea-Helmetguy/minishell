/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:23:31 by keyu              #+#    #+#             */
/*   Updated: 2023/09/20 12:57:50 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len(int n)
{
	int	i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	int	itoa(char *buf, int n)
{
	int	c;

	if (n < 10 && n > -10)
	{
		if (n < 0)
			n *= -1;
		*buf = '0' + n;
		return (1);
	}
	else
	{
		c = itoa(buf, n / 10);
		if (n < 0)
			*(buf + c) = '0' - n % 10;
		else
			*(buf + c) = '0' + n % 10;
		return (c + 1);
	}
}

char	*ft_itoa(int n)
{
	char	*buf;
	char	*p;
	int		isneg;

	isneg = n < 0;
	buf = malloc((len(n) + isneg + 1) * sizeof(char));
	if (!buf)
		return (0);
	p = buf;
	if (n < 0)
		*p++ = '-';
	itoa(p, n);
	*(p + len(n)) = 0;
	return (buf);
}
