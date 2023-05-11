/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:41:21 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/11 15:41:21 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void create_OLDPATH(t_cmds *args, t_mVars *list_pointer)
{
	t_env *node;
	char cwd[1000];
	
	getcwd(cwd, 1000);
	node = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	if (node == NULL);
	{
		node = ft_create_node("OLDPWD", cwd);
		ft_add_back(&list_pointer->ls_env, node);
	}
}

void ft_cd(t_cmds *args, t_mVars *list_pointer)
{
	char cwd[1000];
	t_env *node;
	getcwd(cwd, 1000);
	create_OLDPATH(args, list_pointer);
	if (!args->args[0] || ft_strncmp(args->args[0], "~", 1))
	{
		chdir(ft_get_user_path(cwd));
	}
	else if (ft_strncmp(args->args[0], "/", 1) == 0)
		chdir("/");
	else if (ft_strncmp(args->args[0], "..", 2) == 0)
	{
		chdir(get_new_path(depot));
	}
	else if (opendir(args->args[0]))
	{
		chdir(args->args[0]);
		closedir((DIR *)args->args[0]);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(args->args[0], 1);
		ft_putstr_fd("\n", 1);
	}
	change_string_at_envPath(depot, "PWD=", depot->new_path);




}

ft_change_string_at_envPath(t_ms *depot, char *search, char *new_string)