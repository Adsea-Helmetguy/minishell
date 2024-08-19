/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:36 by mlow              #+#    #+#             */
/*   Updated: 2024/04/14 17:09:49 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ftps_lstlast(t_env *lst)
{
	t_env	*node;

	node = lst;
	while (node && node->next)
	{
		node = node->next;
	}
	return (node);
}

void	ftps_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

	node = ftps_lstlast(*lst);
	if (!node)
		*lst = new;
	else
		node->next = new;
}
