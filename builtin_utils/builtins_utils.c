
#include "../minishell.h"

// int	ft_own_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_strlen(s1) != ft_strlen(s2))
// 		return (1);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

t_env *ft_get_env_node(t_env *head_ref, char *search)
{
	t_env *current;

	if (!(head_ref))
		return NULL;
	current = head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, search) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
