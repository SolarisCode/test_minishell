/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:40:56 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/11 20:28:45 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_ms *depot, char *argument)
{
	pwd(depot, 0);
	depot->old_path = depot->ms_cwd;
	change_string_at_envPath(depot, "OLDPWD=", depot->old_path);
	else if (ft_strncmp(argument, "~", 1) == 0 || !argument)
		chdir(depot->user_path);
	else if (ft_strncmp(argument, "/", 1) == 0)
		chdir("/");
	else if (ft_strncmp(argument, "..", 2) == 0)
	{
		chdir(get_new_path(depot));
	}
	else if (opendir(argument) != NULL)
	{
		chdir(argument);
		closedir((DIR *)argument);
	}
	else
		printf("Pfad konnte nicht gefunden werden\n");
	pwd(depot, 0);
	depot->new_path = depot->ms_cwd;
	change_string_at_envPath(depot, "PWD=", depot->new_path);
}

void ft_unset(t_env **head_ref_env, t_env **head_ref_export, char *env_variable)
{
	unset_export(head_ref_env, env_variable);
	unset_env(head_ref_export, env_variable);
}

void ft_export(t_env **head_ref_env, t_env **head_ref_export, char *data)
{
	t_env *search_node;

	if (!*data)
		print_list(*head_ref_export, print_char);
	search_node = get_env_node(*head_ref_env, data);
	if (search_node == NULL)
	{
		if (!check_valid_env_variable(data))
			add_back(head_ref_env, data);
		add_alphabetical(head_ref_export, data);
	}
	else if (check_variable_argument(*head_ref_env, data) == 0)
	{
		free(search_node->string);
		search_node->string = NULL;
		create_node(search_node, data);
	}
	else
		return;
}
void ft_exit()
{
	exit(1);
}
