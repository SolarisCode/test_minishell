

#include "../minishell.h"

void ft_pushfront_string_env(t_env **head_ref, char *data)
{
	t_env *new_node;

	new_node = ft_create_envnode(data);
	new_node->next = (*head_ref);
	*head_ref = new_node;
}

void ft_print_char(void* data)
{
	ft_putstr_fd((char *)data, 1);
}


void ft_print_list(t_env *head, void (*print)(void*))
{
	t_env *current = head;
	while (current != NULL)
	{
		(*print)(current->var);
		write(1, "=", 1);
		(*print)(current->value);
		write(1, "\n", 1);
		current = current->next;
	}
}

void ft_print_list_export(t_env *head, void (*print)(void*))
{
	t_env *current = head;
	while (current != NULL)
	{
		write(1, "declare -x ", 11);
		(*print)(current->var);
		write(1, "=", 1);
		(*print)(current->value);
		write(1, "\n", 1);
		current = current->next;
	}
}

t_env	*ft_find_previous_node(t_env *head_ref, t_env *node)
{
	t_env *current;

	if (!head_ref)
			return NULL;
	if (head_ref == node)
		return (head_ref);
	current = head_ref;
	while (current->next != node)
		current = current->next;
	return (current);
}

//void sort_alphabetical(t_env **head_ref)
//{
//
//}

void ft_add_alphabetical(t_env **head_ref, char *string)
{
	t_env *new_node;
	new_node = ft_create_envnode(string);
	if (*head_ref == NULL || ft_strcmp(string, (*head_ref)->var) < 0)
	{
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else
	{
		t_env *current = *head_ref;
		t_env *tmp;
		while (current != NULL && ft_strcmp(string, (current)->var) > 0)
		{
			tmp = current;
			printf("compare: %s and %s -> return value: %d\n", string, current->var, ft_strcmp(string, (current)->var));
			current = current->next;
		}

		tmp->next = new_node;
		new_node->next = current;
	}
}
void ft_swap(t_env *a, t_env *b)
{
	char *temp = a->var;
	a->var = b->var;
	b->var = temp;
}

void ft_sort_linked_list(t_env **head_ref)
{
	if (*head_ref == NULL || (*head_ref)->next == NULL)
		return;
	int swapped;
	t_env *current;
	t_env *next = NULL;
	while (1)
	{

		swapped = 0;
		current = *head_ref;
		while (current->next != next)
		{
			if (strcmp(current->var, current->next->var) > 0) {
				ft_swap(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		next = current;
		if (!swapped)
			break;
	}
}

t_env *ft_find_last_node(t_env *head_ref)
{
	t_env *current;

	current = head_ref;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void ft_add_back(t_env **head_ref, t_env *node)
{
	t_env *last_node;

	last_node = ft_find_last_node(*head_ref);
	last_node->next = node;
	node->next = NULL;

}

t_env *ft_create_node(char *var, char *value)
{
	t_env *node;
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	node->var = ft_strdup(var);
	node->value = ft_strdup(value);
	return (node);
}