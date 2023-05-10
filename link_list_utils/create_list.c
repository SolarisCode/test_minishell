#include "../minishell.h"

t_env	*ft_create_envnode(char *string, int index)
{
	t_env	*node;
	char	**str;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	str = ft_split(string, '=');
	node->var = ft_strdup(str[0]);
	node->value = ft_strdup(str[1]);
	node->index = index;
	ft_free_dstr(str);
	return (node);
}

void ft_create_list(t_env *head, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_add_back(head, array[i]);
		i++;
	}
}

t_env *find_last_node(t_env *head_ref)
{
	t_env *current;

	current = head_ref;
	while (current->next != NULL)
		current = current->next;
	printf("%s\n", current->var);
	return (current);
}

void ft_add_back(t_env *head, char *string)
{
	t_env *node;
	t_env *last_node;

	node = ft_create_envnode(string, 1);
	if (head == NULL)
	{
		head->next = node;
		node->next = NULL;
	}
	else
	{
		last_node = find_last_node(head);
		last_node->next = node;
		node->next = NULL;
	}
}