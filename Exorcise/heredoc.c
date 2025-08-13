/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/08/12 20:59:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_here_command(t_tree **tree)
{
	t_redir	*temp;
	int		pipefd[2];
		
	temp = (*tree)->u_define.command.list_redir;
	while ((*tree)->u_define.command.list_redir)
	{
		if ((*tree)->u_define.command.list_redir->type == TK_EOF)
		{
			pipe(pipefd);
			here((*tree)->u_define.command.list_redir->eof, 1, pipefd);
			(*tree)->u_define.command.list_redir->fd_heredoc = pipefd[0];
		}
		(*tree)->u_define.command.list_redir = (*tree)->u_define.command.list_redir->next;
	}
	(*tree)->u_define.command.list_redir = temp;
}

int	here_verify(t_redir *redir, int is_command)
{
	t_redir	*temp;

	if (!redir)
		return (0);
	temp = redir;
	while(temp)
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

void	here(char *eof, int is_command, int *pipefd)
{
	char	*readl;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigkill);
		while (1)
		{
			readl = readline("> ");
			if (ft_strcmp(readl, eof) == 0)
			{
				free(readl);
				exit(0);
				break;
			}
			if (!readl)
			{
				if (is_command == 1)
					close(pipefd[1]);
				exit(0);
				break;
			}
			if (is_command == 1)
			{
				write(pipefd[1], readl, ft_strlen(readl));
				write(pipefd[1], "\n", 1);
			}
			free(readl);
		}
	}
	else
	{
		if (is_command == 1)
			close(pipefd[1]);
		waitpid(pid, &status, 0);
		handle_sigint_in_fork(status, pid);
	}
}

