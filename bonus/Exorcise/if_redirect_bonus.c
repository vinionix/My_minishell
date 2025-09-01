/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_redirect_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/01 01:24:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	if_eof(t_redir *temp)
{
	if (temp->fd_heredoc != -1)
	{
		dup2(temp->fd_heredoc, STDIN_FILENO);
		close(temp->fd_heredoc);
	}
}

static int	if_file_app(t_redir *temp, int current_fd)
{
	current_fd = open(temp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (current_fd == -1)
	{
		perror("miniconsha: fail to open file");
		return (-1);
	}
	else
	{
		dup2(current_fd, STDOUT_FILENO);
		close(current_fd);
	}
	return (0);
}

static int	if_file_out(t_redir *temp, int current_fd)
{
	current_fd = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (current_fd == -1)
	{
		perror("miniconsha: fail to open file");
		return (-1);
	}
	else
	{
		dup2(current_fd, STDOUT_FILENO);
		close(current_fd);
	}
	return (0);
}

static int	if_file_in(t_redir *temp, int current_fd)
{
	current_fd = open(temp->file, O_RDONLY);
	if (current_fd == -1)
	{
		perror("miniconsha: fail to open file");
		return (-1);
	}
	else
	{
		dup2(current_fd, STDIN_FILENO);
		close(current_fd);
	}
	return (0);
}

int	if_redirect(t_redir *list)
{
	int	current_fd;
	int	receiver;

	receiver = 0;
	current_fd = 0;
	while (list)
	{
		if (list->type == TK_EOF)
			if_eof(list);
		else if (list->type == TK_FILE_APP)
			receiver = if_file_app(list, current_fd);
		else if (list->type == TK_FILE_OUT)
			receiver = if_file_out(list, current_fd);
		else if (list->type == TK_FILE_IN)
			receiver = if_file_in(list, current_fd);
		list = list->next;
	}
	return (receiver);
}
