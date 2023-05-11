/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:42:45 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/11 20:15:01 by melkholy         ###   ########.fr       */
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
int		ft_strcmp(char *s1, char *s2);
int		ft_isnonsyscommand(char *arg);
int		ft_env(t_env *envp);
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
//int		ft_export(char **args, t_env **envp);
//int		ft_cd(char **args, t_env *envp);
//int		ft_pwd(void);
//int		ft_unset(char **args, t_env **envp);
//int		ft_echo(char **args);
//void	ft_cmd_analysis(t_cmds *cmd, t_env *env_list);
//void	ft_execute_buildin(t_cmds *cmd, t_env **env_list);

/* builins */
//void ft_cd(t_env *depot, int mode);
void ft_unset(t_env **head_ref_env, t_env **head_ref_export, char *env_variable);
void ft_echo(char *output);
void ft_export(t_env **head_ref_env, t_env **head_ref_export, char *data);
void ft_exit();

/* builtin_utils */
char  *ft_get_user_path(t_env *depot);
void ft_unset_env(t_env **head_ref, char *env_variable);
void ft_unset_export(t_env **head_ref, char *env_variable);
t_env *ft_get_env_node(t_env *head_ref, char *search);
void ft_change_string_at_envPath(t_env *depot, char *search, char *new_string);
char *ft_strncpy(char *source, char c);
char *ft_get_new_path(t_env *depot);
int ft_check_valid_env_variable(char *s);

/* link_list_utils/create_list.c */
t_env	*ft_create_envnode(char *string);
t_env	*ft_get_envp(char **envp);
t_mVars	*ft_create_ls_pointers(char **envp);
void	ft_print_list(t_env *head, void (*print)(void*));
void 	ft_print_list_export(t_env *head, void (*print)(void*));
void	ft_print_char(void* data);
t_env	*ft_find_previous_node(t_env *head_ref, t_env *node);
t_env 	*ft_find_last_node(t_env *head_ref);
void 	ft_add_alphabetical(t_env **head_ref, char *string);
void 	ft_swap(t_env *a, t_env *b);
void 	ft_sort_linked_list(t_env **head_ref);
t_env 	*ft_find_last_node(t_env *head_ref);
void 	ft_add_back(t_env **head_ref, t_env *node);
t_env 	*ft_create_node(char *var, char *value);

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
void	ft_exit_minihell(char *str, t_mVars *list_pointers);
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

#endif
