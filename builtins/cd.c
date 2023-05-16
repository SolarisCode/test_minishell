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

char *ft_malloc_string(char *string)
{
	char *new_string;
	int i;

	i = 0;
	new_string = malloc(ft_strlen(string) + 1);
	while (string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	return (new_string);
}

void ft_update_variable_cd(t_env *node, char *new_value)
{
	free(node->value);
	node->value = NULL;
	node->value = new_value;
}

void ft_create_add_variable(t_env **head_ref, char *var, char *value)
{
	t_env *new_node;

	new_node = ft_create_newnode(value, var);
	ft_add_back(head_ref, new_node);
}

void ft_update_all(t_mVars *list_pointer, char *var)
{
//	char *cwd;

//	cwd = ft_malloc_string(list_pointer->cwd);
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_env, var), ft_strdup(list_pointer->cwd));
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_export, var), ft_strdup(list_pointer->cwd));
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_buffer, var), ft_strdup(list_pointer->cwd));
}

void ft_create_add_all(t_mVars *list_pointer, char *var)
{
//	char *cwd;

//	cwd = ft_malloc_string(list_pointer->cwd);
	ft_create_add_variable(&list_pointer->ls_env, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_create_add_variable(&list_pointer->ls_export, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_create_add_variable(&list_pointer->ls_buffer, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_sort_linked_list(&list_pointer->ls_export);
}

void ft_check_oldpath(t_mVars *list_pointer)
{
	t_env *old_path;
	getcwd(list_pointer->cwd, 1000);
	old_path =  ft_get_env_node(list_pointer->ls_env, "OLDPWD");

	if (list_pointer->check_oldpwd_path == UNSET_BEFORE)
	{
		ft_create_add_all(list_pointer, "OLDPWD");
		list_pointer->check_oldpwd_path = SET;
	}
	old_path =  ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	if (old_path == NULL)
		list_pointer->check_oldpwd_path = UNSET_AFTER;
	if (list_pointer->check_oldpwd_path != UNSET_AFTER)
	{
		ft_update_all(list_pointer, "OLDPWD");
	}
}

void ft_check_pwd(t_mVars *list_pointer)
{
	t_env *pwd_path;

	getcwd(list_pointer->cwd, 1000);
	pwd_path =  ft_get_env_node(list_pointer->ls_env, "PWD");
	if (list_pointer->check_pwd_path == UNSET_BEFORE)
	{
		ft_create_add_all(list_pointer, "PWD");
		list_pointer->check_pwd_path = SET;
	}
	pwd_path =  ft_get_env_node(list_pointer->ls_env, "PWD");
	if (pwd_path == NULL)
		list_pointer->check_pwd_path = UNSET_AFTER;
	if (list_pointer->check_pwd_path != UNSET_AFTER)
	{
		ft_update_all(list_pointer, "PWD");
	}
}

void ft_cd_minus(t_mVars *list_pointer)
{
	t_env *old_path;
	char *save_oldpwd;

	old_path = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	save_oldpwd = ft_strdup(old_path->value);
	ft_check_oldpath(list_pointer);
	chdir(save_oldpwd);
	free(save_oldpwd);
	ft_check_pwd(list_pointer);
}

void ft_cd_dots(t_mVars *list_pointer)
{
	char *new_path;

	ft_check_oldpath(list_pointer);
	new_path = ft_get_new_path(list_pointer->cwd);
	chdir(new_path);
	free(new_path);
	ft_check_pwd(list_pointer);
}

void ft_cd_tilde_empty(t_mVars *list_pointer)
{
	ft_check_oldpath(list_pointer);
	chdir(list_pointer->home);
	ft_check_pwd(list_pointer);
}

void ft_cd_slash(t_mVars *list_pointer)
{
	ft_check_oldpath(list_pointer);
	chdir("/");
	ft_check_pwd(list_pointer);
}

void ft_cd_pathes(t_mVars *list_pointer, char *path)
{
	if (opendir(path) != NULL)
	{
		ft_check_oldpath(list_pointer);
		chdir(path);
		ft_check_pwd(list_pointer);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
}
void ft_cd(t_cmds *cmd, t_mVars *list_pointer)
{
	if (cmd->args == NULL)
		ft_cd_tilde_empty(list_pointer);
	else if (ft_strcmp(cmd->args[0], "-") == 0)
		ft_cd_minus(list_pointer);
	else if (ft_strcmp(cmd->args[0], "..") == 0)
		ft_cd_dots(list_pointer);
	else if (ft_strcmp(cmd->args[0], "~") == 0 || !cmd->args[0])
		ft_cd_tilde_empty(list_pointer);
	else if (ft_strcmp(cmd->args[0], "/") == 0)
		ft_cd_slash(list_pointer);
	else
		ft_cd_pathes(list_pointer, cmd->args[0]);
}

//void ft_cd(t_cmds *cmd, t_mVars *list_pointer)
//{
//	char *new_path;
//
//	if (ft_strcmp(cmd->args[0], "-") == 0)
//	{
//		ft_cd_minus(list_pointer);
//		return;
//	}
//	ft_check_oldpath(list_pointer);
//	if (ft_strcmp(cmd->args[0], "..") == 0)
//	{
//		getcwd(list_pointer->cwd, 1000);
//		new_path = ft_get_new_path(list_pointer->cwd);
//		chdir(new_path);
//		free(new_path);
//	}
//	else if (ft_strcmp(cmd->args[0], "~") == 0 || !cmd->args[0])
//		chdir(list_pointer->home);
//	else if (ft_strcmp(cmd->args[0], "/") == 0)
//		chdir("/");
//	else if (opendir(cmd->args[0]) != NULL)
//	{
//		chdir(cmd->args[0]);
//		closedir((DIR *)cmd->args[0]);
//	}
//	else
//	{
//		ft_putstr_fd("cd: no such file or directory: ", 1);
//		ft_putstr_fd(cmd->args[0], 1);
//	}
//	ft_check_pwd(list_pointer);
//}