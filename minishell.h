/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:44:20 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/23 15:55:41 by gada-sil         ###   ########.fr       */
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

typedef enum e_type
{
	PIPE,
	REDIRECT_APP,
	REDIRECT,
	AND,
	OR,
	HEREDOC,
	COMMAND,
	ARG
}	t_type;

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
	t_type				type;
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