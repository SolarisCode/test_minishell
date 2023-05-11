/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:24:17 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/11 23:42:42 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_execute_buildins(t_cmds *cmd, t_mVars *list_pointer)
{
	(void)list_pointer;
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "/bin/echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->cmd, "env") || !ft_strcmp(cmd->cmd, "/usr/bin/env"))
		ft_env(list_pointer);
	if (!ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "/bin/pwd"))
		ft_pwd();
}
