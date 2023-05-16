
#include "../minishell.h"

// char  *ft_get_user_path(char *path)
// {
// 	char *user_path1;
// 	char *user_path2;
// 	char *user_path3;
// 	char **cwd;

// 	cwd = ft_split(path, '/');
// 	user_path1 = ft_strjoin("/", cwd[0]);
// 	user_path2 = ft_strjoin(user_path1 , "/");
// 	user_path3 = ft_strjoin(user_path2, cwd[1]);
// 	free(user_path1);
// 	free(user_path2);
// 	ft_free_dstr(cwd);
// 	return (user_path3);
// }



int	ft_own_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

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

char *ft_get_new_path(char *s)
{
	int len;
	int i;
	char *new_path;
	len = ft_strlen(s) - 1;
	i = 0;
	while (s[len] != '/')
		len--;
	if (len == 0)
		len = 1;
	new_path = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		new_path[i] = s[i];
		i++;
	}
	new_path[len] = '\0';
	return (new_path);
}
