/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:09:46 by melkholy          #+#    #+#             */
/*   Updated: 2023/04/27 01:40:30 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
# include <fcntl.h>
#include <unistd.h>

int	ft_cmd_size(t_cmds *cmd)
{
	int		count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count ++;
	}
	return (count);
}

char	**ft_create_env_array(t_env	*env_list)
{
	t_env	*tmp_list;
	char	*str;
	char	**env_array;
	int		index;

	index = -1;
	tmp_list = env_list;
	env_array = (char **)ft_calloc(1, sizeof(char *));
	while (tmp_list)
	{
		str = NULL;
		str = ft_join_free_both(ft_strdup(tmp_list->var), ft_strdup("="));
		str = ft_join_free_both(str, ft_strdup(tmp_list->value));
		env_array[++index] = str;
		env_array = ft_double_realloc(env_array, index + 1, index + 2);
		tmp_list = tmp_list->next;
	}
	return (env_array);
}

void	ft_infile_fd(t_cmds *cmd)
{
	int	infile;
	int	status;

	infile = 0;
	status = 0;
	if (access(cmd->from_file, F_OK | R_OK))
	{
		if (access(cmd->from_file, F_OK))
			g_term_attr.status = 1;
		printf("minihell: %s: %s\n", strerror(errno), cmd->from_file);
	}
	else
	{
		infile = open(cmd->from_file, O_RDONLY);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
}

void	ft_outfile_fd(t_cmds *cmd)
{
	int	outfile;
	int	flag;

	flag = 0;
	outfile = 0;
	if (cmd->redirect & OUTPUT)
		flag |= O_TRUNC;
	else if (cmd->redirect & APPEND)
		flag |= O_APPEND;
	if (!access(cmd->to_file, F_OK | W_OK))
		outfile = open(cmd->to_file, O_WRONLY | flag);
	else if (!access(cmd->to_file, F_OK))
	{
		printf("minihell: %s: %s\n", strerror(errno), cmd->to_file);
		g_term_attr.status = 1;
	}
	else
		outfile = open(cmd->to_file, O_RDWR | O_CREAT | flag, 0666);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

void	ft_execute_cmd(t_cmds *cmd, char **env_array)
{
	(void) env_array;
	if ((cmd->redirect & INPUT))
		ft_infile_fd(cmd);
	// if ((cmd->redirect & HEREDOC))
		// printf("Heredoc_end: %s\n", tmp->hdocs_end);
	if ((cmd->redirect & OUTPUT) || (cmd->redirect & APPEND))
		ft_outfile_fd(cmd);
		// printf("To_file: %s\n", tmp->to_file);

}

void	ft_cmd_analysis(t_cmds *cmd, t_env *env_list)
{
	char	**env_array;
	int		pid;

	if (ft_cmd_size(cmd) > 1)
		return ;
	if (!ft_isnonsyscommand(cmd->cmd))
		return ;
	env_array = ft_create_env_array(env_list);
	pid = fork();
	if (pid == 0)
		ft_execute_cmd(cmd, env_array);
	wait(NULL);
}