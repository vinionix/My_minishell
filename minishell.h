/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/06/12 16:39:51 by gada-sil         ###   ########.fr       */
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
# include "Wildcard/wildcard.h"

typedef struct s_tree t_tree;

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
	TK_WORD,
	TK_COMMAND
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	//int					passou _aqui;
	int					id_tree;
	int					id;
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

typedef struct s_pipe
{
	int					pipefd[2];
}						t_pipe;

typedef struct s_command
{
	char				**command;
	const char			*path;
}						t_command;

typedef struct s_and
{
	int					ret;
	struct s_tree		*subshell;
}	t_and;

typedef struct s_or
{
	int					ret;
	t_tree				*subshell;
}	t_or;

typedef struct	s_redir
{
	t_token_type	type;
	int				file_fd;
}	t_redir;

typedef struct	s_heredoc
{
	const char	*eof;
	int			fd_here[2];
}	t_heredoc;

struct s_tree
{
	t_token_type		type;
	int					id;
	union
	{
		t_pipe			pipe;
		t_command		command;
		t_redir			redir;
		t_and			and;
		t_or			or;
		t_heredoc		heredoc;
	} u_define;
	t_tree		*left;
	t_tree		*right;
};

typedef struct	s_head
{
	t_tree	*tree;
}	t_head;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

char					**ft_split(char const *s, char c);
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
int						built_cd(const char **matrix);
int						built_echo(const char **matrix);
int						built_echo_n(const char **matrix);
int						new_var_parsing(t_token *tokens, t_env **envs);
int						built_pwd(const char **matrix);
int						built_env(t_env *env);
void					unset_env_if(t_env **env, const char *target_key);
int						strchr_index(const char *str, char stop);
t_env					*env_new(void);
t_env					*get_env_vars(const char **env);
void					free_matrix(char **matrix);
int						check_flag(const char **matrix);
void					expand_variable(char **matrix, t_env *env_lst);

#endif
