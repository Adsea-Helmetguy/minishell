/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:00:30 by mlow              #+#    #+#             */
/*   Updated: 2023/10/02 17:00:27 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "../libft_project/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 999
# endif

//Main function
char	*get_next_line(int fd);
char	*ft_strjoin2(char const *s1, char const *s2);
int		ft_strlen2(const char *s);
char	*ft_strchr2(const char *s, int c);
char	*ft_free(char **f);
char	*str_combined(char *buf, char *stored_data);
//Files that support get_next_line

#endif
