/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/28 20:40:57 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_here_command(t_tree **tree)
{
	t_redir	*temp;
	int		pipefd[2];

	temp = (*tree)->u_define.command.list_redir;
	while (temp)
	{
		if (temp->type == TK_EOF)
		{
			pipe(pipefd);
			if (here(temp->eof, 1, pipefd))
				temp->fd_heredoc = pipefd[0];
			else
			{
				temp->fd_heredoc = -1;
				close(pipefd[0]);
				close(pipefd[1]);
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
			break ;
		temp = temp->next;
	}
	if (temp && temp->type == TK_EOF && is_command == 1)
		return (1);
	else if (temp && temp->type == TK_EOF && is_command == 0)
		here(temp->eof, 0, 0);
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
	int		status;
	char	*rline[2];

	status = 0;
	rline[1] = NULL;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		rline[0] = readline("");
		expand_variables(rline, get_data()->env);
		if (verify_break(rline, is_command, pipefd, eof) == -1)
			break ;
		free(rline[0]);
	}
	return (1);
}
