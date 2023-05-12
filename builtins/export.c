#include "../minishell.h"


void ft_update_variable(t_env *node, char *new_value)
{
	free(node->value);
	node->value = NULL;
	node->value = ft_strdup(new_value);
	free(new_value);
}

int ft_check_validity(char *s)
{
	int i;

	i = 0;
	if (s[0] == '=')
		return(1);

	while (s[i])
	{
		if (s[i] == '=' && s[i + 1] != '=')
			return (2);
		if (s[i] == '=' && !s[i + 1])
			return (3);
	}
	return (0);
}

void ft_export(t_cmds *cmd, t_mVars *list_pointer)
{
	t_env *search_node;
	int i;
	char **values;
	(void)values;

	i = 0;

	if (!cmd->args)
	{
		ft_print_list(list_pointer->ls_export, ft_print_char);
		return;
	}


	while (cmd->args[i])
	{
		if (ft_check_validity(cmd->args[i]) == 1)
		{
			ft_putstr_fd("export: `", 1);
			ft_putstr_fd(cmd->args[i], 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putstr_fd("\n", 1);
		}
		search_node = ft_get_env_node(list_pointer->ls_env, cmd->args[i]);
		if (ft_check_validity(cmd->args[i]) == 2)
		{
			if (search_node == NULL)
			{
				search_node = ft_create_envnode(cmd->args[i]);
				ft_add_back(&list_pointer->ls_env, search_node);
				ft_add_back(&list_pointer->ls_buffer, search_node);
				ft_add_back(&list_pointer->ls_export, search_node);
				ft_sort_linked_list(&list_pointer->ls_export);
			}
		}
		i++;
	}
}




// while (cmd->args[i])
// 	{
// 		search_node = ft_get_env_node(list_pointer->ls_env, cmd->args[i]);
// 		if (search_node == NULL)
// 		{
// 			if (!ft_check_valid_env_variable(cmd->args[i]))
// 			{
// 				ft_add_back(&list_pointer->ls_env, search_node);
// 				ft_add_back(&list_pointer->ls_buffer, search_node);
// 				ft_add_back(&list_pointer->ls_export, search_node);
// 				ft_sort_linked_list(&list_pointer->ls_export);
// 			}
// 			else
// 			{
// 				values = ft_split(cmd->args[i]);

// 			}
// 		else if (search_node != NULL)
// 		{
// 			ft_update_variable(search_node, cmd->args[i]);
// 		}
// 		i++;
// 	}
