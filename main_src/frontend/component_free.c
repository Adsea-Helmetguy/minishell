/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:33:09 by keyu              #+#    #+#             */
/*   Updated: 2024/07/06 17:35:20 by keyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_component(t_component *component)
{
	if (component->string)
		free(component->string);
	free(component);
}

void	free_components(t_component **components)
{
	int	i;

	i = 0;
	while (components[i])
		free_component(components[i++]);
	free(components);
}
