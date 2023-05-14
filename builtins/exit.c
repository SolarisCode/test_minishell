#include "../minishell.h"

void ft_exit(t_cmds *cmd, t_mVars *list_pointer)
{
	int pid;
	(void)cmd;
	(void)list_pointer;

	pid = fork();
	if (pid == 0)
		exit(0);
}