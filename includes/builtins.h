/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:31:06 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/18 19:33:50 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

void	ft_cd(t_cmds *args, t_mVars *list_pointer);
void	ft_check_oldpath(t_mVars *list_pointer);
void	ft_check_pwd(t_mVars *list_pointer);
/* check_buffer.c*/
void	ft_check_buffer(t_mVars *list_pointer);
/* unset.c */
void	ft_unset(t_cmds *cmd, t_mVars *list_pointer);
void	ft_unset_list(t_env **list_pointer, char *string);
/* echo.c*/
void	ft_echo(t_cmds *node);
int		redirect_echo(t_cmds *cmd, int fd);
int		ft_check_n(char *s);
/* env.c */
void	ft_env(t_mVars *list_pointer);
/* execute_builtins.c */
void	ft_execute_buildins(t_cmds *cmd, t_mVars *list_pointer);
/* exit.c*/
void	ft_exit(void);
/* export.c */
void	ft_export(t_cmds *cmd, t_mVars *list_pointer);
void	check_buffer(char *string, t_env *list_pointer);
void	check_env(char *string, t_env *list_pointer);
void	check_export(char *string, t_env *list_pointer);
void	error_msg(char *string);
/* pwd.c */
void	ft_pwd(void);
/* ################### builtin_utils ################### */
/* cd_utils_1.c*/
void	ft_cd_minus(t_mVars *list_pointer);
void	ft_cd_dots(t_mVars *list_pointer);
void	ft_cd_tilde_empty(t_mVars *list_pointer);
void	ft_cd_slash(t_mVars *list_pointer);
void	ft_cd_pathes(t_mVars *list_pointer, char *path);
/* cd_utils_2.c*/
void	ft_create_add_all(t_mVars *list_pointer, char *var);
void	ft_update_all(t_mVars *list_pointer, char *var);
void	ft_create_add_variable(t_env **head_ref, char *var, char *value);
void	ft_update_variable_cd(t_env *node, char *new_value);
char	*ft_get_new_path(char *s);
/* export_utils_1.c*/
void	update_or_create(t_env *list_pointer, char *string);
void	ft_update_variable(t_env *node, char *new_value);
int		ft_check_validity(char *s);
char	*get_name(char *string);
char	*get_value(char *string);
/* builtin_utils*/
t_env	*ft_get_env_node(t_env *head_ref, char *search);

#endif
