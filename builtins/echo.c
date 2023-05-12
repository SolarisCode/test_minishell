#include "../minishell.h"

int ft_check_n(char *s)
{
	int i;

	i = 1;
	if (s[0] != '-')
		return (1);
	if (s[0] == '-')
	{
		while (s[i])
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
	if (!node->to_file)
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
	fd = 1;
	fd = redirect_echo(node, fd);
	if (fd == 2)
		return;
	if (!node->args[i])
		ft_putstr_fd("\n", fd);
	while (node->args[i])
	{
		if (ft_check_n(node->args[i]) == 1)
		{
			ft_putstr_fd(node->args[i], fd);
			if (node->args[i + 1])
				ft_putstr_fd(" ", fd);
		}
		else
			check_n = 1;
		i++;
	}
	if (check_n == 0)
		ft_putstr_fd("\n", fd);
}


// printf("test\n");
