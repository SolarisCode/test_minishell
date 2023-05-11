/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:09:46 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/11 20:09:34 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <fcntl.h>
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

// void	ft_execute_buildin(t_cmds *cmd, t_env **env_list)
// {
// 	if (!cmd->cmd)
// 		return ;
// 	if (!ft_strcmp(cmd->cmd, "export"))
// 		ft_export(cmd->args, env_list);
// 	else if (!ft_strcmp(cmd->cmd, "env"))
// 		ft_env(*env_list);
// 	else if (!ft_strcmp(cmd->cmd, "cd"))
// 		ft_cd(cmd->args, *env_list);
// 	else if (!ft_strcmp(cmd->cmd, "pwd"))
// 		ft_pwd();
// 	else if (!ft_strcmp(cmd->cmd, "unset"))
// 		ft_unset(cmd->args, env_list);
// 	else if (!ft_strcmp(cmd->cmd, "echo"))
// 		ft_echo(cmd->args);
// }

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

	infile = 0;
	if (!cmd->from_file)
		return ;
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

void	ft_outfile_fd(char *to_file, int redirect)
{
	int	outfile;
	int	flag;

	flag = 0;
	outfile = 0;
	if (redirect & OUTPUT)
		flag |= O_TRUNC;
	else if (redirect & APPEND)
		flag |= O_APPEND;
	if (!access(to_file, F_OK | W_OK))
		outfile = open(to_file, O_WRONLY | flag);
	else if (!access(to_file, F_OK))
	{
		printf("minihell: %s: %s\n", strerror(errno), to_file);
		g_term_attr.status = 1;
	}
	else
		outfile = open(to_file, O_RDWR | O_CREAT | flag, 0666);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

char	*ft_expand_hdoc(char *hdocs_str, t_env *env_list)
{
	char	*str;
	int		count;

	count = 0;
	str = NULL;
	while (hdocs_str[count])
	{
		if (hdocs_str[count] == '$')
			str = ft_join_free_both(str,
					ft_getenv_var(hdocs_str, &count, env_list));
		else
			str = ft_join_free_both(str, ft_substr(&hdocs_str[count], 0, 1));
		count ++;
	}
	free(hdocs_str);
	return (str);
}

int	ft_read_hdocs(char *hdocs_end, t_env *env_list)
{
	char	*str;
	char	*delimiter;
	int		fd;

	delimiter = ft_strjoin(hdocs_end, "\n");
	fd = open("minhell_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(1, "heredoc> ", 9);
	str = get_next_line(0);
	while (ft_strcmp(str, delimiter))
	{
		if (ft_strchr(str, '$'))
			str = ft_expand_hdoc(str, env_list);
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!str)
			break ;
	}
	free(delimiter);
	free(str);
	return (fd);
}

void	ft_here_doc(char **hdocs_end, t_env *env_list)
{
	int		fd;

	if (!access("minhell_tmp.txt", F_OK))
		unlink("minhell_tmp.txt");
	fd = ft_read_hdocs(hdocs_end[0], env_list);
	close(fd);
	if (hdocs_end[1])
		return ;
	fd = open("minhell_tmp.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_execute_redirection(t_cmds *cmd, t_env *env_list)
{
	int	count;

	count = -1;
	if ((cmd->redirect & INPUT))
		ft_infile_fd(cmd);
	if ((cmd->redirect & HEREDOC))
		while (cmd->hdocs_end[++count])
			ft_here_doc(&cmd->hdocs_end[count], env_list);
	if ((cmd->redirect & OUTPUT) || (cmd->redirect & APPEND))
	{
		count = -1;
		while (cmd->to_file[++count])
			ft_outfile_fd(cmd->to_file[count], cmd->redirect);
	}
}

void	ft_execute_cmd(t_cmds *cmd, char **env_array, t_env *env_list)
{
	ft_execute_redirection(cmd, env_list);
	if (!cmd->full_cmd)
		exit(1);
	if (execve(cmd->full_cmd[0], cmd->full_cmd, env_array))
	{
		printf("minihell: %s:%s\n", strerror(errno), cmd->cmd);
		exit(1);
	}
}

void	ft_cmd_analysis(t_cmds *cmd, t_mVars *vars_list)
{
	char	**env_array;
	int		pid;

	if (ft_cmd_size(cmd) > 1)
		return ;
	if (!ft_isnonsyscommand(cmd->cmd))
	{
		env_array = ft_create_env_array(vars_list->ls_buffer);
		pid = fork();
		if (pid == 0)
			ft_execute_cmd(cmd, env_array, vars_list->ls_buffer);
		wait(NULL);
		if ((cmd->redirect & HEREDOC))
			unlink("minhell_tmp.txt");
		ft_free_cmdlist(&cmd);
		ft_free_dstr(env_array);
	}
	else
	{
		ft_execute_buildins(cmd, vars_list);
		ft_free_cmdlist(&cmd);
	}
}
