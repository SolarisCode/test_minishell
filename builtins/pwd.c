#include "../minishell.h"

void ft_pwd()
{
	char cwd[1000];
	getcwd(cwd, 1000);
	ft_putstr_fd(cwd, 1);
}