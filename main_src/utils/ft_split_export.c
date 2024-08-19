/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:05:32 by mlow              #+#    #+#             */
/*   Updated: 2024/05/20 17:50:48 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_tokens_start(char const *s, char c)
{
	size_t	totallength;
	size_t	totalwords;

	totallength = 0;
	totalwords = 0;
	while (s[totallength])
	{
		if (s[totallength] != c && (totallength == 0
				|| s[totallength - 1] == c))
			totalwords++;
		totallength++;
	}
	return (totalwords);
}

static char	*readwords(char const **s, char c, size_t *one_equal)
{
	char	*word;
	size_t	wordlen;
	size_t	string;

	wordlen = 0;
	if (**s == c && **s)
		(*s)++;
	while (**s)
	{
		if (**s == c && *one_equal == 0 && **s)
		{
			(*one_equal)++;
			break ;
		}
		wordlen++;
		(*s)++;
	}
	word = (char *)malloc(sizeof(char) * (wordlen + 1));
	if (!word)
		return (NULL);
	string = -1;
	while (++string < wordlen)
		word[string] = *(*s - wordlen + string);
	word[string] = '\0';
	return (word);
}

static char	**backtrack_free(char **arrays, size_t string)
{
	while ((int)string >= 0)
	{
		free(arrays[string]);
		string--;
	}
	free(arrays);
	return (NULL);
}

char	**ft_split_export(char const *s, char c)
{
	char	**arrays;
	size_t	string;
	size_t	totalwords;
	size_t	one_equal;

	string = 0;
	totalwords = count_tokens_start(s, c);
	arrays = (char **)malloc(sizeof(char *) * (totalwords + 1));
	if (arrays == NULL)
		return (NULL);
	one_equal = 0;
	while (string < totalwords)
	{
		arrays[string] = readwords(&s, c, &one_equal);
		if (!arrays[string])
			return (backtrack_free(arrays, string));
		string++;
	}
	arrays[string] = NULL;
	return (arrays);
}
