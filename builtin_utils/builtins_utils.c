
#include "../minishell.h"

char  *get_user_path(t_ms *depot)
{
	char *user_path1;
	char *user_path2;
	char *user_path3;
	char **cwd;

	cwd = ft_split(depot->ms_cwd, '/');
	user_path1 = ft_strjoin("/", cwd[0]);
	user_path2 = ft_strjoin(user_path1 , "/");
	user_path3 = ft_strjoin(user_path2, cwd[1]);
	free(user_path1);
	free(user_path2);
	ft_free_char_array(cwd);
	return (user_path3);
}

void unset_env(t_env **head_ref, char *env_variable)
{
	t_env *search_node;
	t_env *previous_node;

	printf("check unset_env\n");

	search_node = get_env_node(*head_ref, env_variable);
	if (search_node == NULL)
		return;
	previous_node = find_previous_node(*head_ref, search_node);
	if (search_node == *head_ref)
		*head_ref = (*head_ref)->next;
	else
		previous_node->next = search_node->next;
	free(search_node->string);
	free(search_node);
}

void unset_export(t_env **head_ref, char *env_variable)
{
	t_env *search_node;
	t_env *previous_node;

	printf("check unset_export\n");

	search_node = get_env_node(*head_ref, env_variable);
	if (search_node == NULL)
		return;
	previous_node = find_previous_node(*head_ref, search_node);
	if (search_node == *head_ref)
		*head_ref = (*head_ref)->next;
	else
		previous_node->next = search_node->next;
	free(search_node->string);
	free(search_node);
}

t_env *get_env_node(t_env *head_ref, char *search)
{
	int n;
	t_env *current;

	current = head_ref;
	n = ft_strlen(search);
	while (current->next != NULL)
	{
		if (ft_strncmp(search, current->string, n) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void change_string_at_envPath(t_ms *depot, char *search, char *new_string)
{
	t_env *node;
	char *new_path_string;

	new_path_string = ft_strjoin(search, new_string);
	node = get_env_node(depot->ms_env, search);
	free(node->string);
	node->string = NULL;
	node->string = malloc(sizeof(char) * (ft_strlen(new_path_string) + 1));
	node->string[ft_strlen(new_path_string)] = '\0';
	node->string = new_path_string;
}
char *ft_strncpy(char *source, char c)
{
	int 	i;
	int		j;
	int 	len;
	int n;
	char 	*new_string;

	len = ft_strlen(source);
	new_string = (char *)malloc(sizeof(char) * len);
	i = len;
	n = 0;
	j = 0;
	while (source[i - 1] != c)
	{
		n++;
		i--;
	}
	i = len - n - 1;
	while (i >= 0)
	{
		new_string[j] = source[j];
		i--;
		j++;
	}
	new_string[j] = '\0';
	return (new_string);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

char *get_new_path(t_ms *depot)
{
	depot = NULL;
	char cwd[1000];
	char *new_path;
	int i;

	i = 0;
	getcwd(cwd, 1000);
	new_path = ft_strncpy(cwd, '/');
	return (new_path);
}

//char	*get_folder_path(t_ms *depot)
//{
//	char	**path_folder;
//	char	*command;
//	char	*path_build;
//	char	*command_path;
//	int		i;
//
//	i = 0;
//	path_folder = get_env_path("PWD", 3, depot->ms_env);
//	free(command);
//	while (path_folder[i])
//	{
//		path_build= ft_strjoin("/", path_folder[i]);
//		command_path = ft_strjoin(path_folder[i++], command_built);
//		if (access(command_path, F_OK | X_OK) == 0)
//		{
//			ft_free_char_array(path_folder);
//			free(command_built);
//			return (command_path);
//		}
//		free(command_path);
//	}
//	ft_free_char_array(path_folder);
//	free(command_built);
//	return (NULL);
//}
//
//char	**get_command_arguments(char *arg)
//{
//	char	**arguments;
//
//	arguments = ft_split(arg, ' ');
//	return (arguments);
//}
