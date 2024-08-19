/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:46:55 by mlow              #+#    #+#             */
/*   Updated: 2023/09/30 15:47:21 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static void	ft_convert(char value, va_list args, int *count, int *index)
{
	if (value == 'c')
		return (ft_putc(va_arg(args, int), count));
	else if (value == 's')
		return (ft_putstr(va_arg(args, char *), count));
	else if (value == 'p')
		return (ft_putp(va_arg(args, unsigned long),
				"0123456789abcdef", count));
	else if (value == 'd' || value == 'i')
		return (ft_putdi(va_arg(args, int), count));
	else if (value == 'u')
		return (ft_putu(va_arg(args, unsigned int), count));
	else if (value == 'x')
		return (ft_putx(va_arg(args, unsigned int),
				"0123456789abcdef", count));
	else if (value == 'X')
		return (ft_putx(va_arg(args, unsigned int),
				"0123456789ABCDEF", count));
	else if (value == '%')
		return (ft_putc('%', count));
	else
		((*index)--);
}

int	ft_printf(const char *format, ...)
{
	int		index;
	int		count;
	va_list	args;

	if (!format)
		return (0);
	index = 0;
	count = 0;
	va_start(args, format);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index++;
			ft_convert(format[index], args, &count, &index);
		}
		else
			ft_putc(format[index], &count);
		index++;
	}
	va_end(args);
	return (count);
}
//Starting with ft_printf; the *format is
// the first thing on the list, it is bascially
// the "string" of the printf, which u can do
// the % values that are inside. To handle those,
// we use the va_argument to handle such cases.
//
//To start, we need the va_list, which is a
// "macro" that pass the "Object/variable" 
// we use to define the argument. 
// -------------------------------------------------
// Defination:
// Macro in C programming is known as the piece 
// of code defined with the help of the #define 
// directive. Macros in C are very useful at multiple 
// places to replace the piece of code with a single 
// value of the macro. Macros have multiple types and 
// there are some predefined macros as well.
// It avoids runtime overheads.
//
//
//
// In simple terms:
// A macro is used to substitute a TEXT. 
// For example you want to use a sentence like 
// 'Hey Punit! How are you?' frequently but you 
// don't want to write it again and again or 
// make the code messy. There you can use macro. 
// A macro can be defined for that sentence like 'HEY'. 
// Now whenever you use 'HEY' in your program, 
// it will be replaced by this sentence 
// 'Hey Punit! How are you?'
// -------------------------------------------------
//In our code, that would be "args". 
//Next, we handled the case if "*format" is NULL,
// we return 0 in this situation.
// "Index" is for format[index] & "count" is what 
// we will use to write out the total characters
// we need for our ft_printf such as the words or
// the % stuff.
//
//We then write "va_start(args, format)", the value
// we wrote at va_list will start first, followed by
// the format after for our argument.
// This initialize the function of the va_argument
// so that we can use it for future arguments.
//
//So while the "string format" isnt NULL, we 
// will contiune to read every single char
// and write it out and go to the next one
// UNTIL we hit "%". The if function will then
// read the one after it, skipping the % since
// the original printf don't read and write
// out the % sign. Depending on the what character
// after the %, we will handle it based on
// "ft_convert".
//
//Now going to "ft_convert", i have handled cases
// for cspdiuxX%, 'c' handles single characters,
// 's' a string, 'p' handles the hex which prints
// memory address, 'd' & 'i' handles base 10.
// The reason why both 'd' & 'i' are handled in
// such a way is because they print the same thing
// with printf. They only have difference when
// "scanf" is used.
//
// 'u' for unsigned int, 'x' & 'X' for hexdecimal
// integers for lower & uppcase situation, 
// & '%' just prints '%'.
//
//Once they went through the functions, they will
// return the total count they have earned and/or
// previous count they used to have which counts 
// the total characters in the string.
//
//For 'c', it will first get the value from your
// testcase "s1" and convert it into "int", followed
// by your count, and bring them into "ft_putc".
//
//'s'-testcase "s1" convert into char * cause string,
// & count. etc, etc. Read the rest.
//
//Once you have done so, it will finish "ft_convert"
// which will go back to "ft_printf" which the next
// thing is index++;. This will contiune till the string
// is "NULL" which we will "va_end" which ends the args,
// and return count which will be used by the testcases.
//
//Refer to the other files for more information.
/*
int	ft_printf(const char *format, ...)
{
	int		index;
	int		count;
	va_list args;//list of argument stored

	if (!format)
		return (0);
	index = 0;
	count = 0;
	va_start(args, format);//starting list from format
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index++;
			ft_convert(format[index], args, &count);
			//working to increase count value
			index++;
		}
		else
		{
			ft_putc(format[index], &count);
			index++;
		}
	}
	va_end(args);//end argument
	return (count);
}
*/
//
//va_list is implemented as a POINTER to a structure.
// It holds information about the arguments passed to a 
// function that uses a variable number of arguments.
//We do not need to use * operator to indicate it is
// a pointer because the va_list type is already
// defined as a pointer type. "args" can be passed
// to functions like "va_start", "va_arg" & "va_end"
// to access individual arguments in the list.
