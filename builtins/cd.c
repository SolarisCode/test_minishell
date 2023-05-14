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

void ft_create_add_variable(t_env *list_pointer, char *string)
{
	char *value;
	char *var;
	t_env *new_node;

	var = get_name(string);
	new_node = ft_get_env_node(list_pointer, var);
	value = get_value(string);
	new_node = ft_create_newnode(value, var);
	ft_add_back(&list_pointer, new_node);
}

void ft_check_oldpath(t_mVars *list_pointer, int check)
{
	char *old_path_string;
	t_env *old_path;
	char cwd[1000];
	getcwd(cwd, 1000);
	old_path_string = ft_strjoin("OLDPWD=", cwd);
	printf("old_path: %s\n", old_path_string);
	old_path =  ft_get_env_node(list_pointer->ls_env, "OLDPWD");

	if (check == 0 && old_path == NULL)
	{
		printf("check\n");
		ft_create_add_variable(list_pointer->ls_env, old_path_string);
		ft_create_add_variable(list_pointer->ls_export, old_path_string);
		ft_create_add_variable(list_pointer->ls_buffer, old_path_string);
	}
	if (check == 1 && old_path != NULL)
	{
		ft_update_variable(ft_get_env_node(list_pointer->ls_env, "OLDPWD"), old_path_string);
		ft_update_variable(ft_get_env_node(list_pointer->ls_export, "OLDPWD"), old_path_string);
		ft_update_variable(ft_get_env_node(list_pointer->ls_buffer, "OLDPWD"), old_path_string);
	}
}

void ft_check_pwd(t_mVars *list_pointer, int check)
{
	char *pwd_path_string;
	t_env *pwd_path;
	char cwd[1000];
	getcwd(cwd, 1000);

	pwd_path_string = ft_strjoin("PWD=", cwd);
	printf("cwd: %s\n", cwd);
	printf("actual_path: %s\n", pwd_path_string);
	pwd_path =  ft_get_env_node(list_pointer->ls_env, "PWD");
	if (check == 0 && pwd_path == NULL)
	{
		ft_create_add_variable(list_pointer->ls_env, pwd_path_string);
		ft_create_add_variable(list_pointer->ls_export, pwd_path_string);
		ft_create_add_variable(list_pointer->ls_buffer, pwd_path_string);
	}
	if (check == 1 && pwd_path != NULL)
	{
		ft_update_variable(ft_get_env_node(list_pointer->ls_env, "PWD"), pwd_path_string);
		ft_update_variable(ft_get_env_node(list_pointer->ls_export, "PWD"), pwd_path_string);
		ft_update_variable(ft_get_env_node(list_pointer->ls_buffer, "PWD"), pwd_path_string);
	}
}

void ft_cd(t_cmds *cmd, t_mVars *list_pointer)
{
	static int check;

	check = 0;
	getcwd(list_pointer->cwd, 1000);
	list_pointer->old_path = list_pointer->cwd;
	ft_check_oldpath(list_pointer, check);

	if (ft_strcmp(cmd->args[0], "_") == 0)
		chdir(list_pointer->old_path);
	if (ft_strcmp(cmd->args[0], "..") == 0)
	{
		chdir(ft_get_new_path(list_pointer->cwd));
		printf("%s\n",ft_get_new_path(list_pointer->cwd));
	}
	if (ft_strcmp(cmd->args[0], "~") == 0)
		chdir(list_pointer->home);
	if (ft_strcmp(cmd->args[0], "/") == 0)
		chdir("/");
	else
	{
		chdir(cmd->args[0]);
	}
	ft_check_pwd(list_pointer, check);
	ft_sort_linked_list(&list_pointer->ls_export);
	check += 1;
}