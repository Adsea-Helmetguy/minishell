/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:13:12 by mlow              #+#    #+#             */
/*   Updated: 2023/10/05 12:10:07 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft_project/libft.h"

char	*ft_free(char **f)
{
	if (*f)
	{
		free(*f);
		*f = NULL;
	}
	return (NULL);
}

char	*str_combined(char *buf, char *stored_data)
{
	char	*temp_data;

	temp_data = stored_data;
	temp_data = ft_strjoin2(stored_data, buf);
	ft_free(&stored_data);
	return (temp_data);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	str1;
	size_t	str2;
	char	*newstr;

	str1 = 0;
	str2 = 0;
	newstr = (char *)malloc(sizeof(char)
			* ((ft_strlen2(s1) + ft_strlen2(s2)) + 1));
	if (!newstr)
		return (NULL);
	while (s1[str1] != '\0')
	{
		newstr[str1] = s1[str1];
		str1++;
	}
	while (s2[str2] != '\0')
	{
		newstr[str1 + str2] = s2[str2];
		str2++;
	}
	newstr[str1 + str2] = '\0';
	return (newstr);
}

int	ft_strlen2(const char *s)
{
	int	length_so_far;

	length_so_far = 0;
	if (!s)
		return (0);
	while (s[length_so_far] != '\0')
	{
		length_so_far++;
	}
	return (length_so_far);
}

char	*ft_strchr2(const char *s, int c)
{
	int		num_source;
	char	character;

	character = (char)c;
	if (character == '\0')
		return ((char *)s + ft_strlen2(s));
	num_source = 0;
	while (s[num_source] != '\0')
	{
		if (s[num_source] == character)
			return ((char *)s + num_source);
		num_source++;
	}
	return (NULL);
}

//
/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	num_s;
	size_t	num_st;
	char	*substring;

	num_s = 0;
	num_st = (size_t)start;
	if (!s)
		return (NULL);
	if (start >= ft_strlen2(s))
		return (ft_strdup(""));
	if (len > ft_strlen2(s) - start)
		len = ft_strlen2(s) - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	while (s[num_s + num_st] && (num_s < len))
	{
		substring[num_s] = s[num_s + num_st];
		num_s++;
	}
	substring[num_s] = '\0';
	return (substring);
}

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		i;

	dest = (char *)malloc(sizeof(char) * (ft_strlen2(s) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
*/
