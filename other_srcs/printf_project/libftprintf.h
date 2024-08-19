/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:33:32 by mlow              #+#    #+#             */
/*   Updated: 2023/09/27 17:20:28 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdarg.h>
# include <limits.h>

//Main function
int		ft_printf(const char *format, ...);
//Files that support ft_printf
void	ft_putc(int c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_putdi(int nb, int *count);
void	ft_putu(unsigned int nb, int *count);
void	ft_putx(unsigned int nb, char *base, int *count);
void	ft_putp(unsigned long nb, char *base, int *count);

#endif
