/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/26 03:02:34 by vfidelis         ###   ########.fr       */
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
# include <sys/wait.h>

void					logi(int x);
void					logfl(float x);
void					logd(double x);
void					logc(char x);
void					logs(const char *x);

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
	struct s_env		*next;
}						t_env;

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

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	char				*eof;
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
}						t_pipe;

typedef struct s_operators
{
	int	result1;
	int	result2;
	int	valid;
}						t_operators;

typedef struct s_tree
{
	t_token_type		type;
	int					n_builtin;
	int					id_tree;
	int					main;
	union
	{
		t_pipe			pipe;
		t_operators		operators;
		t_command		command;
	} u_define;
	struct s_tree		*left;
	struct s_tree		*right;
	struct s_tree		*prev;
	struct s_tree		*subtree;
}						t_tree;

typedef	struct s_process
{
	pid_t				pid;
	t_tree				*dad;
	int					id_tree;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

char					**ft_split(char const *s, char c);
char					**creat_command(int id_command, t_token *tokens);
char					*built_pwd(void);
void					tree_creator(t_token **tokens, t_tree **tree, int id);
void					ft_lexer(t_token **tokens);
void					free_split(char **input);
void					free_tokens(char **matrix, t_token *tokens);
void					envadd_back(t_env **lst, t_env *new);
void					unset_env_if(t_env **env, const char *target_key);
void					process_creator(t_tree **tree, t_process **process);
int						sintaxe_error(t_token **tokens);
int						ft_len_matrix(char **matrix);
int						jump_char(char chr);
int						chr_separator(char *input, int i);
int						tokenizer(t_arg_main *args);
int						env_lstsize(t_env *lst);
int						built_cd(const char *str);
int						built_echo(const char *str);
int						built_echo_n(const char *str);
int						new_var_parsing(t_token *tokens, t_env **envs);
int						built_env(t_env *env);
int						strchr_index(const char *str, char stop); 
t_tree					*last_left(t_tree *tree);
t_env					*env_new(void);
t_env					*get_env_vars(const char **env);

#endif
