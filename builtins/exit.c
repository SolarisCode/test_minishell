#include "../minishell.h"

void ft_exit(t_cmds *cmd, t_mVars *list_pointer)
{
	int pid;

	pid = fork();
	if (pid == 0)
		exit(0);
}