/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/09/01 01:06:09 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../consha.h"

void	creat_here_command(t_tree **tree)
{
	t_redir	*temp;
	int		pipefd[2];

	temp = (*tree)->u_define.command.list_redir;
	while (temp)
	{
		if (temp->type == TK_EOF && temp->fd_heredoc == -1)
		{
			pipe(pipefd);
			if (here(temp->eof, 1, pipefd))
				temp->fd_heredoc = pipefd[0];
			if (here_verify(temp->next, 1))
			{
				close(pipefd[0]);
				temp->fd_heredoc = -1;
			}
		}
		temp = temp->next;
	}
}

int	here_verify(t_redir *redir, int is_command)
{
	t_redir	*temp;

	if (!redir)
		return (0);
	temp = redir;
	while (temp)
	{
		if (temp->type == TK_EOF)
		{
			if (is_command == 0)
				here(temp->eof, 0, 0);
			else
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int	verify_break(char **rline, int is_command, int *pipefd, char *eof)
{
	if (ft_strcmp(rline[0], eof) == 0 || !rline[0])
	{
		if (rline[0])
			free(rline[0]);
		if (is_command == 1)
			close(pipefd[1]);
		return (-1);
	}
	if (is_command == 1)
	{
		write(pipefd[1], rline[0], ft_strlen(rline[0]));
		write(pipefd[1], "\n", 1);
	}
	return (0);
}

int	here(char *eof, int is_command, int *pipefd)
{
	char	*rline[2];

	rline[1] = NULL;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		rline[0] = readline("↪︎ ");
		expand_variables(rline, get_data()->env);
		if (verify_break(rline, is_command, pipefd, eof) == -1)
			return (1);
		free(rline[0]);
	}
	signal(SIGINT, handle_sigint_no_redisplay);
	return (1);
}
