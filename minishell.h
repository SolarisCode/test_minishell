/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:03:01 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/12 14:47:15 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include "./Libft/libft.h"
#define PROMPT "\033[35mminihell\033[36m$\033[0m "
#define DIRECTION_ERR "minishell: syntax error near unexpected token"
#define INPUT 1
#define HEREDOC 2
#define OUTPUT 4
#define APPEND 8
#define UNSET_BEFORE 3
#define UNSET_AFTER 4
#define SET 5
/* Node to store the commands in a linked list */
typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	char			**full_cmd;
	char			*from_file;
	char			**hdocs_end;
	char			**to_file;
	int				redirect;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;


typedef struct s_mVars
{
	t_env			*ls_env;
	t_env			*ls_export;
	t_env			*ls_buffer;
	char			*home;
	char			cwd[1000];
	char 			*old_path;
	int 			check_pwd_path;
	int 			check_oldpwd_path;
	int				check_cd_minus;
}				t_mVars;
/* A global variable to store the term attributes and exit status */
typedef struct s_term
{
	struct termios	save_attr;
	int				status;
}				t_term;

t_term	g_term_attr;

void	ft_convertsyscommands(t_cmds *cmd, t_env *envp);
char	**ft_getpaths(t_env *envp);
int		ft_checkpaths(char *command, char **paths);
void	ft_freepaths(char **paths);
int		ft_issyscommand(char *cmd, t_env *envp);
int		ft_isnonsyscommand(char *arg);
void	ft_addnewnode(char *arg, t_env *tmp, t_env **envp);
int		ft_check_and_edit_existing_var(char **args, t_env *tmp, int i);
int		ft_checklistlen(t_env *envp);
void	ft_printinorder(t_env *envp, int *indexprinted);
int		ft_isnotprinted(t_env *envp, int *indexprinted, int withcostumvars);
int		ft_isbeforeinalph(char *varname, char *tmpvar);
int		ft_isvalididentifier(char c);
int		ft_checkforwrongargs(char **args);
void	ft_setindexprinted(t_env *envp, int index, int *indexprinted);
char	*ft_getvarname(char *arg);
char	*ft_getvarvalue(char *arg);
void	ft_printnextalpha(t_env *envp, int *indexprinted);

/* builins */
//void ft_cd(t_env *depot, int mode);
void	ft_unset(t_cmds *cmd, t_mVars *list_pointer);
void	ft_echo(t_cmds *node);
void	ft_pwd();
void	ft_cd(t_cmds *args, t_mVars *list_pointer);
void	ft_env(t_mVars *list_pointer);
void	ft_export(t_cmds *cmd, t_mVars *list_pointer);
void	ft_execute_buildins(t_cmds *cmd, t_mVars *list_pointer);
void 	ft_exit(t_cmds *cmd, t_mVars *list_pointer);
void	ft_check_buffer(t_mVars *list_pointer);

/* builtin_utils */
// char  *ft_get_user_path(t_env *depot);
t_env	*ft_get_env_node(t_env *head_ref, char *search);
char	*ft_get_new_path(char *s);
int		ft_check_valid_env_variable(char *s);
void	ft_unset_list(t_env **list_pointer, char *string);

// export_utils

char	*get_value(char *string);
char	*get_name(char *string);
int		ft_check_validity(char *s);
void	ft_update_variable(t_env *node, char *new_value);
void	update_or_create(t_env *list_pointer, char *string);

/* link_list_utils/create_list.c */
t_env	*ft_create_envnode(char *string);
t_env	*ft_get_envp(char **envp);
t_mVars	*ft_create_ls_pointers(char **envp);
void	ft_print_list(t_env *head, void (*print)(void*));
void	ft_print_list_export(t_env *head, void (*print)(void*));
void	ft_print_char(void* data);
t_env	*ft_find_previous_node(t_env *head_ref, t_env *node);
t_env	*ft_find_last_node(t_env *head_ref);
void	ft_add_alphabetical(t_env **head_ref, char *string);
void	ft_swap(t_env *a, t_env *b);
void	ft_sort_linked_list(t_env **head_ref);
t_env	*ft_find_last_node(t_env *head_ref);
void	ft_add_back(t_env **head_ref, t_env *node);
void	ft_create_cd_variables(t_mVars *list_pointer);
t_env	*ft_create_envnode(char *string);
t_env 	*ft_create_node(char *var, char *value);
t_env	*ft_create_newnode(char *value, char *var);
void	ft_free_node(t_env *node);

/* input_analysis.c */
void	ft_create_fullcmd(t_cmds *cmd);
void	ft_free_cmdlist(t_cmds **cmds);
char	*ft_find_envpath(t_env *env_list);
int		ft_add_path(t_cmds *cmd, t_env *env_list);
void	ft_parse_input(char *in_put, t_mVars *vars_list);

/* lexer.c */
char	*ft_expansion(char *str, t_env *env_list);
char	*ft_getenv_var(char *in_put, int *index, t_env *env_list);
char	*ft_inside_qoutes(char *str, char *in_put,
		int *index, t_env *env_list);
char	*ft_tokenize(char *str, char *in_put, int *index, t_env *env_list);
char	**ft_lexer(char *in_put, t_env *env_list);

/* parsing_redirection.c */
char	*ft_add_io_file(char *old_file, char *new_file, int len);
void	ft_arrange_table(char **table, int index, int len);
int		ft_add_redirection(char **table, t_cmds *cmd, int index, int len);
int		ft_get_redirection(char *in_put);
int		ft_check_redirect(t_cmds *cmd, char **cmd_table);

/* parser.c */
t_cmds	*ft_parser(char **cmd_table);
t_cmds	*ft_many_cmd(t_cmds *cmd, char **full_cmds, t_env *env_list);
char	*ft_cut_input(char *in_put, int *index);
char	**ft_check_pipe_char(char *in_put);
t_cmds	*ft_text_analysis(char *in_put, t_env *env_list);

/* parsing_utils.c */
int		ft_isnspace_indx(char *in_put);
void	ft_free_dstr(char **str);
char	**ft_check_args(char *arg, char **cmd_args);
char	**ft_double_realloc(char **str, int old_size, int new_size);
char	*ft_join_free_both(char *s1, char *s2);

/* signals.c */
void	ft_quit_ignore(int sig);
int		ft_set_terminal(void);

/* main.c */
int		ft_read_prompt(char **envp);
void	ft_exit_minihell(char *str, t_cmds *cmd, t_mVars *list_pointers);
void	ft_free_envlist(t_env **env_list);
int		ft_closing_qoutes(char *in_put);

/* execution.c */
int		ft_cmd_size(t_cmds *cmd);
void	ft_infile_fd(t_cmds *cmd);
char	**ft_create_env_array(t_env	*env_list);
void	ft_outfile_fd(char *to_file, int redirect);
char	*ft_expand_hdoc(char *hdocs_str, t_env *env_list);
int		ft_read_hdocs(char *hdocs_end, t_env *env_list);
void	ft_here_doc(char **hdocs_end, t_env *env_list);
void	ft_execute_redirection(t_cmds *cmd, t_env *env_list);
void	ft_execute_cmd(t_cmds *cmd, char **env_array, t_env *env_list);
void	ft_cmd_analysis(t_cmds *cmd, t_mVars *vars_list);
int		ft_is_builtin(char* cmd);
int		ft_strcmp(char *s1, char *s2);


#endif
