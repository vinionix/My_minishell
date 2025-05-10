/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/02 04:12:17 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <errno.h>
# include "libft/libft.h"

void logi(int x);
void logfl(float x);
void logd(double x);
void logc(char x);
void logs(const char *x);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

#define log_var(x) _Generic((x), \
    int: log_int, \
    float: log_float, \
    double: log_double, \
    char: log_char, \
    char *: log_str, \
    const char *: log_str)

typedef enum e_token_type
{
	TK_REDIR_IN = 1,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_FILE_IN,
	TK_FILE_OUT,
	TK_FILE_APP,
	TK_EOF,
	TK_WORD,
	TK_COMMAND
}	t_token_type;

/*typedef enum e_bultin
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	B_OR,
	B_REDIR_IN,
	B_REDIR_OUT,
	B_APPEND,
	B_HEREDOC,
	B_EOF
}	t_bultin;*/

typedef struct s_token
{
	t_token_type	type;
	int				id;
	bool			is_env;
	char			*value;
}	t_token;

typedef struct s_arg_main
{
	char	*rdline;
	char	*rdline2;
	char	**matrix;
	char	*temp;
	char	*temp2;
	char	*return_join;
	t_token	*tokens;
	int		i;
}	t_arg_main;


typedef struct s_pipe
{
	int		pipefd[2];
}	t_pipe;

typedef struct s_command
{
	char		**command;
	const char	*path;
}	t_command;

typedef struct s_commander
{
	t_token_type		type;
	int					n_builtin;
	union
	{
		t_pipe			pipe;
		t_command		command;
	}					u_define;
	struct s_commander	*left;
	struct s_commander	*right;
}	t_commander;

int		ft_len_matrix(char  **matrix);
int		jump_char(char chr);
int		chr_separator(char *input, int i);
int		tokenizer(t_arg_main *args);
char	**ft_split(char const *s, char c);
void	ft_lexer(t_token **tokens);
void	free_split(char **input);
void    sintaxe_error(t_token **tokens);
t_env	*env_new(void);
int		env_lstsize(t_env *lst);
void	envadd_back(t_env **lst, t_env *new);
int    built_cd(const char *str);
int    built_echo(const char *str);
int    built_echo_n(const char *str);
char  *built_pwd(void);

#endif
