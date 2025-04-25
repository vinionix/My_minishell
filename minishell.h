/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/24 20:37:42 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
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
# include "libft/libft.h"

void logi(int x);
void logfl(float x);
void logd(double x);
void logc(char x);
void logs(const char *x);

#define log_var(x) _Generic((x), \
    int: log_int, \
    float: log_float, \
    double: log_double, \
    char: log_char, \
    char *: log_str, \
    const char *: log_str)

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_OPEN_PAREN,
	TK_CLOSE_PAREN,
	TK_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

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

void    parsing(const char *input);
void    bi_cd(const char *str);
void    bi_pwd();

#endif