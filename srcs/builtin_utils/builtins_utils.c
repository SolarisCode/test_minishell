/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:46:29 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/18 18:46:52 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_env_node(t_env *head_ref, char *search)
{
	t_env	*current;

	if (!(head_ref))
		return (NULL);
	current = head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, search) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
