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
	while (temp)
	{
		if (temp->type == TK_EOF)
		{
			pipe(pipefd);
			here(temp->eof, 1, pipefd);
			temp->fd_heredoc = pipefd[0];
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
	pid_t	pid;
	int		status;
	char	*rline[2];

	status = 0;
	pid = fork();
	rline[1] = NULL;
	if (pid == 0)
	{
		signal(SIGINT, handle_sigkill);
		while (1)
		{
			rline[0] = readline("> ");
			expand_variables(rline, get_data()->env);
			if (ft_strcmp(rline[0], eof) == 0)
			{
				free(rline[0]);
				exit(0);
				break;
			}
			if (!rline[0])
			{
				if (is_command == 1)
					close(pipefd[1]);
				exit(0);
				break;
			}
			if (is_command == 1)
			{
				write(pipefd[1], rline[0], ft_strlen(rline[0]));
				write(pipefd[1], "\n", 1);
			}
			free(rline[0]);
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

