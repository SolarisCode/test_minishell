/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscommands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:01 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/05/11 21:37:47 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_issyscommand(char *cmd, t_env *envp)
{
	char	**paths;
	int		pathnum;

	pathnum = 0;
	paths = ft_getpaths(envp);
	pathnum = ft_checkpaths(cmd, paths);
	ft_free_dstr(paths);
	if (pathnum >= 0)
		return (1);
	else
		return (0);
}


int	ft_isnonsyscommand(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env")
		|| !ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}
