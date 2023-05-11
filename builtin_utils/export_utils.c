#include "../../inc/minishell.h"

int ft_check_variable_argument(t_env *head_ref, char *data)
{
	char **variable_path;
	char **variable_new;
	int ret;

	ret = 0;

	variable_path = ft_split(head_ref->string, '=');
	variable_new = ft_split(data, '=');
	if (variable_path[1] == variable_new[1])
		ret = 1;
	ft_free_char_array(variable_new);
	ft_free_char_array(variable_path);
		return (ret);
}

//int ft_check_existence(t_env **head_ref, char *s)
//{
//
//}

int ft_check_valid_env_variable(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (s[i++] == '=')
			return (0);
	return (1);
}

//char *get_variable_name(char *string)
//{
//	int i;
//	char *variable_name;
//
//	i = 0;
//	if (check_variable_argument(string) == 0)
//		return (string);
//	if (ft_strchr(string, '=') )
//	while(string[i] != '=')
//		i++;
//	variable_name = malloc(sizeof(char) * (i + 1));
//	ft_strlcpy(variable_name, string, i + 1);
//	return (variable_name);
//}

//void change_variable_value(t_env *node, char *new_value)
//{
//	char *variable
//
//
//
//}