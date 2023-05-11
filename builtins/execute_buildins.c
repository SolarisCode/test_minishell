/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:24:17 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/11 18:24:17 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_execute_buildins(t_cmds *cmd, t_mVars *list_pointer)
{
	(void)list_pointer;
	ft_echo(cmd);
	ft_env(list_pointer);
	ft_pwd();
}