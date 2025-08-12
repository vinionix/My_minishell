/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/08/09 05:34:54 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>

void					logi(int x);
void					logfl(float x);
void					logd(double x);
void					logc(char x);
void					logs(const char *x);

extern volatile sig_atomic_t signal_v;

typedef enum e_token_type
{
	TK_REDIR_IN = 1,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_FINAL_PAREN,
	TK_INIT_PAREN,
	TK_FILE_IN,
	TK_FILE_OUT,
	TK_FILE_APP,
	TK_EOF,
	TK_CMD_ARG,
	TK_COMMAND 
}						t_token_type;

typedef struct s_env
{
	char				*key;
	char				*value;
	bool				printed;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	t_token_type		type;
	int					id;
	int					passed;
	char				*value;
}						t_token;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	char				*eof;
	int					fd_heredoc;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**cmd;
	const char			*path;
	t_redir				*list_redir;
}						t_command;

typedef struct s_pipe
{
	int					pipefd[2];
	int					std_in;
}						t_pipe;

typedef struct s_tree
{
	t_token_type		type;
	int					id_tree;
	int					main;
	union
	{
		t_pipe			pipe;
		t_command		command;
	} u_define;
	struct s_tree		*left;
	struct s_tree		*right;
	struct s_tree		*prev;
	struct s_tree		*subtree;
}						t_tree;

typedef struct s_data
{
	int					exit_code;
	t_env				*env;
	t_tree				*head;
	bool				exited_in_fork;
	bool				should_redisplay;
}						t_data;

typedef struct s_arg_main
{
	char				*rdline;
	char				**matrix;
	char				*temp;
	t_token				*tokens;
	t_tree				*tree;
	int					i;
}						t_arg_main;

typedef	struct s_process
{
	pid_t				pid;
	t_tree				*dad;
	int					id_tree;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

char					**ft_split(char const *s, char c);
void					free_list(t_env *env);
char					*format_input(char *input);
char					**creat_command(int id_command, t_token *tokens);
char					*built_pwd(void);
char					**get_path(t_env *env);
char					*get_pwd(void);
char					*get_pwd(void);
char					**wildcard(char **matrix);
char					**expand_and_wildcard(char **matrix, t_env *env_lst);
unsigned char			ft_exit(char **matrix, t_tree *tree, t_env *env);
void					tree_creator(t_token **tokens, t_tree **tree, int id);
void					free_tree(t_tree *tree);
void					ft_lexer(t_token **tokens);
void					free_split(char **input);
void					process_add_back(t_process **main, t_process *node);
void					change_cwd(t_env *env_list);
void					free_tokens(char **matrix, t_token *tokens);
void					envadd_back(t_env **lst, t_env *new);
void					ft_pipe(t_tree **tree, int left_or_rigth);
void					exorcise_manager(t_tree **tree);
void					exorcise(t_tree *current_node, int flag);
void					wait_free_process(t_process **process);
void					ft_clean_and_exit(t_env *env, t_tree *tree, unsigned int exit_code);
void					creat_solo_redirect(t_redir *redir);
void					here(char *eof, int is_command, int *pipefd);
void					free_matrix(char **matrix);
void					expand_variables(char **matrix, t_env *env_lst);
void					creat_here_command(t_tree **tree);
int						here_verify(t_redir *redir, int is_command);
int						sintaxe_error(t_token **tokens);
int						ft_len_matrix(char **matrix);
int						jump_char(char chr);
int						chr_separator(char *input, int i);
int						tokenizer(t_arg_main *args);
int						env_lstsize(t_env *lst);
int						valid_path(char **cmd, char **path);
int						ft_cd(char **matrix, t_env *env_list);
int						check_home(char *str);
void					parse_home(char **matrix, int home, t_env *env_list);
int						ft_echo(char **matrix);
int						ft_echo_n(char **matrix);
int						new_var_parsing(char **matrix, t_env **envs);
int						ft_pwd(char **matrix);
int						ft_env(t_env *env, char **matrix);
unsigned char			ft_exit(char **matrix, t_tree *tree, t_env *env);
char					*get_pwd(void);
int						ft_unset(char **matrix, t_env **envs);
int						unset_env_if(t_env **env, const char *target_key);
int						strchr_index(const char *str, char stop);
int						check_flag(char **matrix);
int						ft_export(char **matrix, t_env **envs);
int						export_no_args(t_env *envs);
t_data					*get_data(void);
t_env					*env_new(void);
t_env					*get_env_vars(const char **env);
t_env					*find_env(const char *target_key, t_env *envs);
t_process				*node_process_creator(t_tree *node);
t_process				*search_process(t_process **process, t_tree *current_node);
t_tree					*last_left(t_tree *tree);
bool					verify_ls_flag(char **matrix);
char					**expand_and_wildcard(char **matrix, t_env *env_lst);
void					ft_clean_and_exit(t_env *env, t_tree *tree, unsigned int exit_code);
unsigned long long		ft_atol(char *str, int *sign);
int						jump_to_smt_else(const char *str, char c, int i);
void					change_env_var(t_env *envs, char *env_to_change, char *value);
void					create_default_env(t_env **envs);
int						exec_builtin(char ***matrix, t_env **envs, t_tree *tree);
int						jump_to(const char *str, char c, int i);
bool					have_char(char *str, char c);
void					check_priority(t_token **tokens, int i, int *receiver, int *flag);
int						find_next_r(t_token **tokens, int start, int receiver, int flag);
int						search_left(t_token **tokens, int id);
int						search_right(t_token **tokens, int id);
t_tree					*search_for_bigger(t_token **tokens);
t_tree					*node_creator(t_token **tokens, int id);
t_redir					*creat_list_redir(int id, t_token **tokens);
bool					is_builtin(char *command);
void					free_list_redir(t_redir *list);
void					handle_sigint(int sig);
void					set_signal(void);
int						handle_sigint_in_fork(int status, pid_t pid);

#endif
