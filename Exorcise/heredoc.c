/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:58:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/07/23 07:58:16 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_here_command(t_tree **tree)
{
	t_redir	*temp;
	int		pipefd[2];
		
	temp = (*tree)->u_define.command.list_redir;
	pipe(pipefd);
	while ((*tree)->u_define.command.list_redir)
	{
		if ((*tree)->u_define.command.list_redir->type == TK_EOF)
		{
			here((*tree)->u_define.command.list_redir->eof, 1, pipefd);
			(*tree)->u_define.command.list_redir->fd_heredoc = pipefd[0];
		}
		(*tree)->u_define.command.list_redir = (*tree)->u_define.command.list_redir->next;
	}
	(*tree)->u_define.command.list_redir = temp;
}

int	here_verify(t_redir *redir)
{
	t_redir	*temp;

	if (!redir)
		return (0);
	temp = redir;
	while(temp)
	{
		if (temp->type == TK_EOF)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	here(char *eof, int is_command, int *pipefd)
{
	char	*readl;

	while (1)
	{
		readl = readline("> ");
		if (!readl)
		{
			if (is_command == 1)
				close(pipefd[1]);
			break;
		}
		if (ft_strcmp(readl, eof) == 0)
		{
			free(readl);
			break;
		}
		if (is_command == 1)
		{
			write(pipefd[1], readl, ft_strlen(readl));
			write(pipefd[1], "\n", 1);
		}
		free(readl);
	}
	if (is_command == 1)
	{
		close(pipefd[1]);
	}
}

