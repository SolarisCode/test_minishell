#include "../minishell.h"

t_env	*ft_create_envnode(char *string)
{
	t_env	*node;
	char	**str;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	str = ft_split(string, '=');
	node->var = ft_strdup(str[0]);
	node->value = ft_strdup(str[1]);
	ft_free_dstr(str);
	return (node);
}

t_env	*ft_get_envp(char **envp)
{
	int		count;
	t_env	*head;
	t_env	*tmp;

	count = 0;
	head = ft_create_envnode(envp[count]);
	if (!head)
		return (NULL);
	tmp = head;
	while (envp[++count])
	{
		tmp->next = ft_create_envnode(envp[count]);
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
	}
	return (head);
}

t_mVars	*ft_create_ls_pointers(char **envp)
{
	t_mVars	*list_pointer;

	list_pointer = (t_mVars *)ft_calloc(1, sizeof(t_mVars));
	list_pointer->ls_env = ft_get_envp(envp);
	list_pointer->ls_export = ft_get_envp(envp);
	list_pointer->ls_buffer = ft_get_envp(envp);
	return (list_pointer);
}
