/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:32:35 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/18 19:34:55 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINK_LIST_H
# define LINK_LIST_H

# include "structs.h"

/* ################### link_list_utils ################### */
/* link_list_utils_1*/
void	ft_add_back(t_env **head_ref, t_env *node);
t_env	*ft_find_last_node(t_env *head_ref);
void	ft_free_node(t_env *node);
void	ft_sort_linked_list(t_env **head_ref);
void	ft_swap(t_env *a, t_env *b);
/* link_list_utils_2*/
void	ft_create_cd_variables(t_mVars *list_pointer);
t_mVars	*ft_create_ls_pointers(char **envp);
t_env	*ft_get_envp(char **envp);
t_env	*ft_create_newnode(char *value, char *var);
t_env	*ft_create_envnode(char *string);
/* link_list_utils_3*/
t_env	*ft_find_previous_node(t_env *head_ref, t_env *node);
void	ft_print_list_export(t_env *head, void (*print)(void*));
void	ft_print_list(t_env *head, void (*print)(void*));
void	ft_print_char(void *data);
void	ft_pushfront_string_env(t_env **head_ref, char *data);

#endif
