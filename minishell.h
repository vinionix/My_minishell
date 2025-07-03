/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/11 18:21:43 by vfidelis         ###   ########.fr       */
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
# include <unistd.h>

void					logi(int x);
void					logfl(float x);
void					logd(double x);
void					logc(char x);
void					logs(const char *x);

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

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

typedef struct s_token
{
	t_token_type		type;
	int					id;
	int					passed;
	char				*value;
}						t_token;

typedef struct s_arg_main
{
	char				*rdline;
	char				**matrix;
	char				*temp;
	t_token				*tokens;
	int					i;
}						t_arg_main;

typedef struct s_command
{
	char				**cmd;
	const char			*path;
}						t_command;

typedef struct s_pipe
{
	int					pipefd[2];
}						t_pipe;

typedef struct s_operators
{
	int	result1;
	int	result2;
}						t_operators;

typedef struct s_redir
{
	int	fd;
}						t_redir;

typedef struct s_here
{
	char *eof;
}						t_here;

typedef struct s_tree
{
	t_token_type		type;
	int					n_builtin;
	int					id_tree;
	union
	{
		t_pipe			pipe;
		t_redir			redir;
		t_here			here;
		t_operators		operators;
		t_command		command;
	} u_define;
	struct s_tree		*left;
	struct s_tree		*right;
	struct s_tree		*prev;
	struct s_tree		*subtree;
}						t_tree;

char					**ft_split(char const *s, char c);
char					**creat_command(int id_command, t_token *tokens);
void					tree_creator(t_token **tokens, t_tree **tree, int id);
void					ft_lexer(t_token **tokens);
void					free_split(char **input);
void					free_tokens(char **matrix, t_token *tokens);
void					envadd_back(t_env **lst, t_env *new);
int						sintaxe_error(t_token **tokens);
int						ft_len_matrix(char **matrix);
int						jump_char(char chr);
int						chr_separator(char *input, int i);
int						tokenizer(t_arg_main *args);
int						env_lstsize(t_env *lst);
int						ft_cd(char **matrix, t_env *env_list);
int						ft_echo(char **matrix);
int						ft_echo_n(char **matrix);
int						new_var_parsing(char **matrix, t_env **envs);
int						ft_pwd(char **matrix);
int						ft_env(t_env *env);
char					*get_pwd(void);
void					unset_env_if(t_env **env, const char *target_key);
int						strchr_index(const char *str, char stop);
t_env					*env_new(void);
t_env					*get_env_vars(const char **env);
void					free_tree(t_tree *tree);
void					free_matrix(char **matrix);
int						check_flag(char **matrix);
t_env					*find_env(const char *target_key, t_env *envs);
void					change_cwd(t_env *env_list);
char					*get_pwd(void);
void					expand_variables(char **matrix, t_env *env_lst);
int						ft_export(char **matrix, t_env **envs);
char					**wildcard(char **matrix);
bool					have_char(char *str, char c);
bool					verify_ls_flag(char **matrix);
char					**expand_and_wildcard(char **matrix, t_env *env_lst);

#endif
