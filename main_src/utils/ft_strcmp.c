/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:55:31 by mlow              #+#    #+#             */
/*   Updated: 2024/03/13 20:55:37 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_env	*string_compare(char *cmd_array, t_mini *mini, int i)
{
	int		string_l;
	t_env	*e;

	e = mini->envpmen;
	string_l = ft_strlen(e->name);
	while (d_strncmp(cmd_array, e->name, string_l, i) != 0)
	{
		if (!(e->next))
			return (NULL);
		e = e->next;
		string_l = ft_strlen(e->name);
	}
	mini->found_length -= (string_l + 1);
	return (e);
}

int	d_strncmp(char *s1, char *s2, size_t n, int index)
{
	size_t			num;
	unsigned char	*ss1;
	unsigned char	*ss2;

	num = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((ss1[num + index] != '\0' && ss2[num] != '\0') && num < n)
	{
		if (ss1[num + index] != ss2[num])
			return (ss1[num + index] - ss2[num]);
		num++;
	}
	if (ss2[num] == '\0')
	{
		if (invalid_char((char *)ss1, (num + index)) == 0)
			return (0);
	}
	return (ss1[num + index] - ss2[num]);
}
