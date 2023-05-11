#include "../minishell.h"

int ft_export(char *s)
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