/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:41:21 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/12 14:16:26 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void create_OLDPATH(t_mVars *list_pointer)
// {
// 	t_env *node;
// 	char cwd[1000];

// 	getcwd(cwd, 1000);
// 	node = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
// 	if (node == NULL)
// 	{
// 		node = ft_create_node("OLDPWD", cwd);
// 		ft_add_back(&list_pointer->ls_env, node);
// 	}
// }

// void ft_cd(t_cmds *args, t_mVars *list_pointer)
// {
// 	char cwd[1000];
// 	t_env *node;
// 	(void)node;
// 	getcwd(cwd, 1000);
// 	create_OLDPATH(list_pointer);
// 	if (!args->args[0] || !ft_strcmp(args->args[0], "~"))
// 	{
// 		printf("test\n");
// 		chdir(ft_get_env_node(list_pointer->ls_buffer, "HOME")->value);
// 	}
// 	else if (ft_strncmp(args->args[0], "/", 1) == 0)
// 		chdir("/");
// 	// else if (ft_strncmp(args->args[0], "..", 2) == 0)
// 	// {
// 	// 	chdir(get_new_pathlist_pointer->ls_env));
// 	// }
// 	else if (opendir(args->args[0]))
// 	{
// 		chdir(args->args[0]);
// 		closedir((DIR *)args->args[0]);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("cd: no such file or directory: ", 1);
// 		ft_putstr_fd(args->args[0], 1);
// 		ft_putstr_fd("\n", 1);
// 	}




// }

