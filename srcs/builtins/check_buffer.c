/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:54:05 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/18 18:54:10 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_buffer(t_mVars *list_pointer)
{
	ft_print_list_export(list_pointer->ls_buffer, ft_print_char);
}
