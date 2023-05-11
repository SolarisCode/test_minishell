/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:42:45 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/11 20:06:15 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

// char	*ft_realloc(char *str, int old_size, int new_size)
// {
// 	char	*tmp;
// 	int		count;
//
// 	tmp = (char *)ft_calloc(new_size + 1, sizeof(char));
// 	count = 0;
// 	while (count < old_size)
// 	{
// 		tmp[count] = str[count];
// 		count ++;
// 	}
// 	free(str);
// 	return (tmp);
// }

// void	ft_arrange_args(t_cmds *cmd, int index, int len)
// {
// 	if (!cmd->args[index][len])
// 	{
// 		free(cmd->args[index]);
// 		free(cmd->args[index + 1]);
// 		while (cmd->args[index + 2])
// 		{
// 			cmd->args[index] = cmd->args[index + 2];
// 			index ++;
// 		}
// 		cmd->args[index] = NULL;
// 		return ;
// 	}
// 	free(cmd->args[index]);
// 	cmd->args[index] = cmd->args[index + 1];
// 	while (cmd->args[++index])
// 		cmd->args[index] = cmd->args[index + 1];
// }

// char	**ft_cmd_table(char **cmd_table, char *str, int index)
// {
// 	cmd_table[index] = ft_strdup(str);
// 	cmd_table = ft_double_realloc(cmd_table, index + 1, index + 2);
// 	free(str);
// 	return (cmd_table);
// }
char	*ft_find_envpath(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp("PATH", current->var))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}


int	ft_add_path(t_cmds *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**env_path;
	int		count;

	cmd_path = NULL;
	count = -1;
	env_path = ft_split(ft_find_envpath(env_list), ':');
	while (env_path[++count])
		env_path[count] = ft_strjoin_free(env_path[count], "/");
	count = -1;
	while (env_path[++count])
	{
		cmd_path = ft_strjoin(env_path[count], cmd->cmd);
		if (!access(cmd_path, F_OK | X_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_free_dstr(env_path);
	if (!cmd_path)
		return (printf("minihell: command not found: %s\n", cmd->cmd));
	free(cmd->cmd);
	cmd->cmd = cmd_path;
	return (0);
}

void	ft_free_cmdlist(t_cmds **cmds)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		*cmds = (*cmds)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			ft_free_dstr(tmp->args);
		if (tmp->full_cmd)
			ft_free_dstr(tmp->full_cmd);
		if ((tmp->redirect & INPUT))
			free(tmp->from_file);
		if ((tmp->redirect & HEREDOC))
			ft_free_dstr(tmp->hdocs_end);
		if ((tmp->redirect & OUTPUT) || (tmp->redirect & APPEND))
			ft_free_dstr(tmp->to_file);
		free(tmp);
		tmp = *cmds;
	}
}

void	ft_create_fullcmd(t_cmds *cmd)
{
	char	**full_cmd;
	int		count;

	count = 0;
	if (!cmd->cmd)
		return ;
	full_cmd = (char **)ft_calloc(1, sizeof(char *));
	full_cmd[count] = ft_strdup(cmd->cmd);
	full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
	while (cmd->args && cmd->args[count])
	{
		full_cmd[count + 1] = ft_strdup(cmd->args[count]);
		count ++;
		full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
	}
	cmd->full_cmd = full_cmd;
}

/* Used to check the input and pass it to the parsing and cutting
 functions to get back either a linked list with all the command original
 just one command in a node */
void	ft_parse_input(char *in_put, t_mVars *vars_list)
{
	t_cmds	*cmd;
	t_cmds	*tmp;
	int		count;

	count = 0;
	count += ft_isnspace_indx(in_put);
	if (!in_put[count])
		return ;
	cmd = ft_text_analysis(&in_put[count], vars_list->ls_buffer);
	free(in_put);
	if (!cmd)
		return ;
	tmp = cmd;
	while (tmp)
	{
		// ft_convertsyscommands(cmd, env_list);
		// if (!ft_add_path(cmd, env_list))
		// 	ft_create_fullcmd(cmd);
		ft_add_path(cmd, vars_list->ls_buffer);
		ft_create_fullcmd(cmd);
		tmp = tmp->next;
	}
	ft_cmd_analysis(cmd, vars_list);
	/* The rest of the function is for demonstration purposes
	  to make sure the lexer is working well*/
	// t_cmds *tmp;
	// tmp = cmd;

	// while (tmp)
	// {
	// 	count = 0;
	// 	printf("Command: %s\n", tmp->cmd);
	// 	while (tmp->args && tmp->args[count])
	// 	{
	// 		printf("Arg %d: %s\n", count, tmp->args[count]);
	// 		count ++;
	// 	}
	// 	if ((tmp->redirect & INPUT))
	// 		printf("From_file: %s\n", tmp->from_file);
	// 	if ((tmp->redirect & HEREDOC))
	// 		printf("Heredoc_end: %s\n", tmp->hdocs_end);
	// 	if ((tmp->redirect & OUTPUT) || (tmp->redirect & APPEND))
	// 		printf("To_file: %s\n", tmp->to_file);
	// 	tmp = tmp->next;
	// }
	// ft_execute_buildin(cmd, env_list); //placing this here causes no problems
}
