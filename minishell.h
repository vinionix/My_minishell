/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/27 15:27:18 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define POSSIBLE_ENV_MARKER '\x1E'
# define SINGLE_QUOTE_MARKER '\x1F'
# define DOUBLE_QUOTE_MARKER '\x1C'
# define DOLLAR_MARKER '\x01'

void							logi(int x);
void							logfl(float x);
void							logd(double x);
void							logc(char x);
void							logs(const char *x);

extern volatile sig_atomic_t	g_signal_v;

typedef enum e_token_type
{
	TK_REDIR_IN = 1,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_PIPE,
	TK_FILE_IN,
	TK_FILE_OUT,
	TK_FILE_APP,
	TK_EOF,
	TK_CMD_ARG,
	TK_COMMAND,
}								t_token_type;

typedef struct s_env
{
	char						*key;
	char						*value;
	bool						printed;
	struct s_env				*next;
}								t_env;

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	char						*eof;
	int							fd_heredoc;
	struct s_redir				*next;
}								t_redir;

typedef struct s_command
{
	char						**cmd;
	const char					*path;
	t_redir						*list_redir;
}								t_command;

typedef struct s_pipe
{
	int							pipefd[2];
	int							std_in;
}								t_pipe;

typedef struct s_tree
{
	t_token_type				type;
	int							id_tree;
	int							main;
	union
	{
		t_pipe					pipe;
		t_command				command;
	} u_define;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_tree				*prev;
}								t_tree;

typedef struct s_token
{
	t_token_type				type;
	int							id;
	int							passed;
	char						*value;
}								t_token;

typedef struct s_data
{
	int							exit_code;
	t_env						*env;
	t_tree						*head;
	bool						exited_in_fork;
	int							is_subshell;
}								t_data;

typedef struct s_arg_main
{
	char						*rdline;
	char						**matrix;
	char						*temp;
	t_token						*tokens;
	t_tree						*tree;
	int							i;
}								t_arg_main;

typedef struct s_process
{
	pid_t						pid;
	t_tree						*dad;
	int							id_tree;
	struct s_process			*prev;
	struct s_process			*next;
}								t_process;

unsigned char					ft_exit(char **matrix, t_tree *tree,
									t_env *env);
unsigned char					ft_exit(char **matrix, t_tree *tree,
									t_env *env);
char							**ft_split(char const *s, char c);
char							*format_input(char *input);
char							**creat_command(int id_command,
									t_token *tokens);
char							*built_pwd(void);
char							**get_path(t_env *env);
char							*get_pwd(void);
char							*get_pwd(void);
char							**wildcard(char **matrix);
char							**expand_and_quotes(char **matrix,
									t_env *env_lst);
char							**expand_and_wildcard(char **matrix,
									t_env *env_lst);
char							*get_pwd(void);
void							tree_creator(t_token **tokens, t_tree **tree,
									int id);
void							free_list(t_env *env);
void							free_tree(t_tree *tree);
void							ft_lexer(t_token **tokens);
void							free_split(char **input);
void							process_add_back(t_process **main,
									t_process *node);
void							change_cwd(t_env *env_list);
void							free_tokens(t_token *tokens);
void							envadd_back(t_env **lst, t_env *new);
void							ft_pipe(t_tree **tree, int left_or_rigth);
void							exorcise_manager(t_tree **tree);
void							exorcise(t_tree *current_node, int std_out);
void							wait_free_process(t_process **process);
void							ft_clean_and_exit(t_env *env, t_tree *tree,
									unsigned int exit_code);
void							creat_solo_redirect(t_redir *redir);
void							free_matrix(char **matrix);
void							expand_variables(char **matrix, t_env *env_lst);
void							creat_here_command(t_tree **tree);
int								here(char *eof, int is_command, int *pipefd);
int								here_verify(t_redir *redir, int is_command);
int								sintaxe_error(t_token **tokens);
int								ft_len_matrix(char **matrix);
int								jump_char(char chr);
int								chr_separator(char *input, int i);
int								tokenizer(t_arg_main *args);
int								env_lstsize(t_env *lst);
int								valid_path(char **cmd, char **path);
int								ft_cd(char **matrix, t_env *env_list);
int								check_home(char *str);
int								parse_home(char **matrix, t_env *env_list);
int								change_dir(char *str);
int								ft_echo(char **matrix);
int								ft_echo_n(char **matrix);
int								new_var_parsing(char **matrix, t_env **envs);
int								ft_pwd(char **matrix);
int								ft_env(t_env *env, char **matrix);
int								ft_unset(char **matrix, t_env **envs);
int								unset_env_if(t_env **env,
									const char *target_key);
int								strchr_index(const char *str, char stop);
int								check_flag(char **matrix);
int								ft_export(char **matrix, t_env **envs);
int								export_no_args(t_env *envs);
t_data							*get_data(void);
t_env							*env_new(void);
t_env							*get_env_vars(const char **env);
t_env							*find_env(const char *target_key, t_env *envs);
t_process						*node_process_creator(t_tree *node);
t_process						*search_process(t_process **process,
									t_tree *current_node);
t_tree							*last_left(t_tree *tree);
void							ft_clean_and_exit(t_env *env, t_tree *tree,
									unsigned int exit_code);
unsigned long long				ft_atol(char *str, int *sign);
int								jump_to_smt_else(const char *str, char c,
									int i);
void							change_env_var(t_env *envs, char *env_to_change,
									char *value);
void							create_default_env(t_env **envs);
int								exec_builtin(char ***matrix, t_env **envs,
									t_tree *tree);
int								jump_to(const char *str, char c, int i);
bool							have_char(char *str, char c);
void							check_priority(t_token **tokens, int i,
									int *receiver, int *flag);
int								find_next_r(t_token **tokens, int start,
									int receiver, int flag);
int								search_left(t_token **tokens, int id);
int								search_right(t_token **tokens, int id);
t_tree							*search_for_bigger(t_token **tokens);
t_tree							*node_creator(t_token **tokens, int id, int i);
t_redir							*creat_list_redir(int id, t_token **tokens);
bool							is_builtin(char *command);
void							free_list_redir(t_redir *list);
void							handle_sigint(int sig);
void							set_signal(void);
int								handle_sigint_in_fork(int status, pid_t pid);
void							handle_sigkill(int sig);
void							handle_sigint_code(void);
int								handle_sigint_in_heredoc(int status, pid_t pid);
void							copy_token(t_token *new, t_token *tokens);
void							copy_children(t_token *tokens, t_token *new,
									int i, int size);
void							assign_subshell_token(t_token *new,
									t_token *tokens);
t_data							*get_data(void);
t_token							*size_new_tokens(t_token *tokens);
int								get_subshell_size(t_token *tokens, int i);
void							free_old_tokens(t_token *tokens);
int								if_redirect(t_redir *list);
void							free_tree_and_env(void);
void							exec_command_solo(t_tree *current_node);
void							creat_solo_redirect(t_redir *redir);
t_process						*node_process_creator(t_tree *node);
void							process_add_back(t_process **main,
									t_process *node);
void							free_tree_and_env(void);
t_tree							*last_left(t_tree *tree);
char							**env_execv(t_env *env);
void							print_error(char *error_message, char *token);
int								check_consecutive_operators(t_token **tokens,
									int i);
int								check_last_token(t_token **tokens, int i);
int								check_first_token(t_token **tokens, int i);
void							assign_value(t_token **tokens, int i,
									int receiver);
int								create_head(t_tree **tree, t_token **tokens);
int								count_quotes_right(char *str, char c);
int								count_quotes_left(char *str, int i, char c);
void							parse_quotes(char **matrix);
void							reset_modified_chars(char **matrix, char c);
void							remove_quotes(char **matrix);

#endif
