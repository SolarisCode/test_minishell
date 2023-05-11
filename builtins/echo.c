#include "../minishell.h"

int ft_check_n(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
	{
		while (s[i] == 'n' && s[i])
		{
			if (s[i] != 'n')
				return (1);
			i++;
		}
	}
	return 0;
}

int redirect_echo(t_cmds *node, int fd)
{
	int i;

	i = 0;
	if (!node->to_file[i])
		return (1);
	while (node->to_file[i])
		i++;
	const char* filename = node->to_file[i - 1];
	mode_t filePermissions = S_IRUSR | S_IWUSR;
	fd = open(filename, O_WRONLY | O_CREAT, filePermissions);
	if (fd == -1)
	{
		perror("Error opening the file\n");
		return 2;
	}
	return (fd);
}
void ft_echo(t_cmds *node)
{
	int i;
	int check_n;
	int fd;

	i = 0;
	check_n = 0;
	fd = redirect_echo(node, fd);
	if (fd == 2)
		return;
	if (!node->args[i])
		ft_putstr_fd("\n", fd);
	while (node->args[i])
	{
		if (i != 0)
			ft_putstr_fd(" ", fd);
		if (ft_check_n(node->args[i]) == 0)
		{
			ft_putstr_fd(node->args[i], fd);
		}
		else
			check_n = 1;
		i++;
	}
	if (check_n == 0)
		ft_putstr_fd("\n", fd);

}